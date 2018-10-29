/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scanner.cpp
 * Author: thewaffledimension
 * 
 * Created on October 26, 2018, 12:50 PM
 */

#include "Scanner.h"
#include "Log.h"

Scanner::Scanner(std::string source) : source(source) {
    indents.push(indent);
    altIndents.push(altIndent);
}

Scanner::Scanner(const Scanner& orig) {
}

Scanner::~Scanner() {
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    
    if (!brackets.empty()) {
        for (int i = 0; i < brackets.size(); i++) {
            Log::error(brackets.top(), "Unclosed bracket");
            brackets.pop();
        }
    }
    
    addToken(TokenType::END_OF_FILE);
    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    
    int prevLine = line;
    
    if (atbol) {
        indent = 0;
        altIndent = 0;
        
        while (true) {
            if (isAtEnd()) break;
            
            if (c == '\t') {
                indent++;
                
                for (int i = 0; i < 8; i++) {
                    if (indent % 8 == 0) break;
                    indent++;
                }
                
                altIndent++;
            } else if (c == ' ') {
                indent++;
                altIndent++;
            } else {
                break;
            }
            
            c = advance();
        }
        
        if (indent == indents.top() && altIndent == altIndents.top()) {
            // Do nothing, indentation is the same.
        } else if (indent > indents.top() && altIndent > altIndents.top()) {
            // Indentation.
            addToken(TokenType::INDENT, previous());
            indents.push(indent);
            altIndents.push(altIndent);
        } else if (indent < indents.top() && altIndent < altIndents.top()) {
            // Dedentation.
            bool found = false;
            
            for (int i = 0; i < indents.size(); i++) {
                if (indent == indents.top() && altIndent == altIndents.top()) {
                    found = true;
                    break;
                }
                
                indents.pop();
                altIndents.pop();
                addToken(TokenType::DEDENT, previous());
            }
            
            if (!found) {
                Log::error(line, column, "Did not find previous block with same indentation.");
            }
        } else {
            Log::error(line, column, "Indentation is invalid.");
        }
        
        atbol = false;
    }
    
    switch(c) {
        case '(': addToken(TokenType::LEFT_PAREN); brackets.push(line); break;
        case ')': addToken(TokenType::RIGHT_PAREN); brackets.pop(); break;
        case '{': addToken(TokenType::LEFT_BRACE); brackets.push(line); break;
        case '}': addToken(TokenType::RIGHT_BRACE); brackets.pop(); break;
        case '[': addToken(TokenType::LEFT_SQUARE); brackets.push(line); break;
        case ']': addToken(TokenType::RIGHT_SQUARE); brackets.pop(); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.':
            if (match('.') && match('.')) {
                addToken(TokenType::ELIPSIS);
            } else {
                addToken(TokenType::DOT);
            }
            break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case '^': addToken(TokenType::BIT_XOR); break;
        case '&': addToken(match('&') ? TokenType::AND : TokenType::BIT_AND); break;
        case '|': addToken(match('|') ? TokenType::OR : TokenType::BIT_OR); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case ':': addToken(TokenType::COLON); break;
        case '*': addToken(match('*') ? TokenType::EXPONENT : TokenType::STAR); break;
        case '?': addToken(TokenType::QUESTION); break;
        
        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        
        case '$': addToken(TokenType::SIGIL); break;
        
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line
                while (peek() != '\n' && !isAtEnd()) advance();
            } else if (match('*')) {
                // Multiline comment
                while (peek() != '*' && peekNext() != '/' && !isAtEnd()) advance();
                advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
            
        case '#':
            if (match('*')) {
                while (peek() != '*' && peekNext() != '#' && !isAtEnd()) advance();
                advance();
            } else {
                while (peek() != '\n' && !isAtEnd()) advance();
            }
            break;
            
        case '"': string(); break;
        
        case '\r':
        case ' ':
        case '\t':
            break;
            
        case '\n':
            if (brackets.empty() && previous() != '\\') {
                atbol = true;
            }
            line++;
            column = 0;
            break;
            
        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                Log::error(line, column, "Unexpected character.");
            }
            break;
    }
    
    if (prevLine == line) {
        atbol = false;
    }
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            line++;
            column = 0;
        }
        advance();
    }
    
    if (isAtEnd()) {
        Log::error(line, column, "Unterminated string.");
        return;
    }
    
    advance(); // Closing "
    
    // Trim the surrounding quotes
    std::string value = source.substr(start + 1, current - 1);
    addToken(TokenType::STRING, value);
}

void Scanner::number() {
    while (isDigit(peek())) advance();
    
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the '.'
        advance();
        
        while (isDigit(peek())) advance();
    }
    
    addToken(TokenType::NUMBER, std::stod(source.substr(start, current)));
}

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();
    
    // See if the identifier is a reserved keyword.
    std::string text = source.substr(start, current);
    TokenType type = TokenType::IDENTIFIER;
    if (keywords.count(text) == 1) {
        type = keywords[text];
    }
    
    addToken(type);
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
    return ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_'));
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

char Scanner::advance() {
    char c = source.at(current);
    current++;
    column++;
    return c;
}

char Scanner::previous() {
    return source.at(current - 1);
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source.at(current);
}

char Scanner::peekNext() {
    if (current + 1 >= source.length() || isAtEnd()) return '\0';
    return source.at(current + 1);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;
    
    current++;
    return true;
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::addToken(TokenType type) {
    addToken(type, NULL);
}

void Scanner::addToken(TokenType type, std::any literal) {
    std::string text = source.substr(start, current);
    tokens.push_back(Token(type, text, literal, line, column));
}