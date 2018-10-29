/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.cpp
 * Author: thewaffledimension
 * 
 * Created on October 28, 2018, 10:18 PM
 */

#include "Parser.h"
#include "Log.h"

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
    
}

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> statements;
    
    while (!isAtEnd()) {
        std::unique_ptr<Stmt> stmt = std::move(declaration());
        if (stmt)
            statements.push_back(std::move(stmt));
    }
    
    return statements;
}

std::unique_ptr<Stmt> Parser::declaration() {
    try {
        return std::move(statement());
    } catch (ParseError error) {
        synchronize();
        return nullptr;
    }
}

std::unique_ptr<Stmt> Parser::statement() {
    if (match({TokenType::IF})) return std::move(ifStatement());
    if (match({TokenType::INDENT})) return std::unique_ptr<Stmt>(new Stmt::Block(std::move(block())));
    
    return std::move(expressionStatement());
}

std::unique_ptr<Stmt> Parser::ifStatement() {
    std::unique_ptr<Expr> condition = std::move(expression());
    
    consume(TokenType::COLON, "Expect ':' after condition.");
    
    std::unique_ptr<Stmt> ifBody = nullptr;
    if (match({TokenType::INDENT})) {
        ifBody = std::unique_ptr<Stmt>(new Stmt::Block(std::move(block())));
    } else {
        ifBody = std::move(declaration());
    }
    
    std::unique_ptr<Stmt> elseBody = nullptr;
    if (match({TokenType::ELSE})) {
        consume(TokenType::COLON, "Expect ':' after 'else'.");
        if (match({TokenType::INDENT})) {
            elseBody = std::unique_ptr<Stmt>(new Stmt::Block(std::move(block())));
        } else {
            elseBody = std::move(declaration());
        }
    } else if (match({TokenType::ELSEIF})) {
        elseBody = std::move(ifStatement());
    }
    
    return std::unique_ptr<Stmt>(new Stmt::If(std::move(condition), std::move(ifBody), std::move(elseBody)));
}

std::vector<std::unique_ptr<Stmt>> Parser::block() {
    std::vector<std::unique_ptr<Stmt>> statements;
    
    while (!match({TokenType::DEDENT}) && !isAtEnd()) {
        std::unique_ptr<Stmt> stmt = declaration();
        if (stmt) {
            statements.push_back(std::move(stmt));
        }
    }
    
    return std::move(statements);
}

std::unique_ptr<Stmt> Parser::expressionStatement() {
    std::unique_ptr<Expr> expr = expression();
    return std::unique_ptr<Stmt>(new Stmt::Expression(std::move(expr)));
}

std::unique_ptr<Expr> Parser::expression() {
    return std::move(assignment());
}

std::unique_ptr<Expr> Parser::assignment() {
    std::unique_ptr<Expr> expr = bitwise();
    
    if (match({TokenType::EQUAL})) {
        Token equals = previous();
        std::unique_ptr<Expr> value = assignment();
        
        if (Util::instanceof<Expr::Variable>(expr.get())) {
            Token name = dynamic_cast<Expr::Variable*>(expr.get())->name;
            return std::unique_ptr<Expr>(new Expr::Assign(name, std::move(value)));
        }
        
        error(equals, "Invalid assignment target.");
    }
    
    return std::move(expr);
}

std::unique_ptr<Expr> Parser::bitwise() {
    std::unique_ptr<Expr> expr = logical();
    
    while (match({TokenType::BIT_AND, TokenType::BIT_OR, TokenType::BIT_XOR})) {
        Token op = previous();
        std::unique_ptr<Expr> right = logical();
        expr = std::unique_ptr<Expr>(new Expr::Binary(std::move(expr), op, std::move(right)));
    }
    
    return std::move(expr);
}

std::unique_ptr<Expr> Parser::logical() {
    std::unique_ptr<Expr> expr = equality();
    
    while (match({TokenType::AND, TokenType::OR})) {
        Token op = previous();
        std::unique_ptr<Expr> right = equality();
        expr = std::unique_ptr<Expr>(new Expr::Binary(std::move(expr), op, std::move(right)));
    }
    
    return std::move(expr);
}

std::unique_ptr<Expr> Parser::equality() {
    std::unique_ptr<Expr> expr = comparison();
    
    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        Token op = previous();
        std::unique_ptr<Expr> right = comparison();
        expr = std::unique_ptr<Expr>(new Expr::Binary(std::move(expr), op, std::move(right)));
    }
    
    return std::move(expr);
}

std::unique_ptr<Expr> Parser::comparison() {
    std::unique_ptr<Expr> expr = addition();
    
    while (match({TokenType::GREATER, TokenType::LESS, TokenType::GREATER_EQUAL, TokenType::LESS_EQUAL, TokenType::SIGN})) {
        Token op = previous();
        std::unique_ptr<Expr> right = addition();
        expr = std::unique_ptr<Expr>(new Expr::Binary(std::move(expr), op, std::move(right)));
    }
    
    return std::move(expr);
}

std::unique_ptr<Expr> Parser::addition() {
    std::unique_ptr<Expr> expr = multiplication();
    
    while (match({TokenType::PLUS, TokenType::MINUS})) {
        Token op = previous();
        std::unique_ptr<Expr> right = multiplication();
        expr = std::unique_ptr<Expr>(new Expr::Binary(std::move(expr), op, std::move(right)));
    }
    
    return std::move(expr);
}

std::unique_ptr<Expr> Parser::multiplication() {
    std::unique_ptr<Expr> expr = unary();
    
    while (match({TokenType::SLASH, TokenType::STAR, TokenType::EXPONENT})) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();
        expr = std::unique_ptr<Expr>(new Expr::Binary(std::move(expr), op, std::move(right)));
    }
    
    return std::move(expr);
}

std::unique_ptr<Expr> Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS})) {
        Token op = previous();
        std::unique_ptr<Expr> right = unary();
        return std::unique_ptr<Expr>(new Expr::Unary(op, std::move(right)));
    }
    
    return std::move(primary());
}

std::unique_ptr<Expr> Parser::primary() {
    if (match({TokenType::FALSE})) return std::unique_ptr<Expr>(new Expr::Literal(false));
    if (match({TokenType::TRUE})) return std::unique_ptr<Expr>(new Expr::Literal(true));
    if (match({TokenType::NIL})) return std::unique_ptr<Expr>(new Expr::Literal(NULL));
    
    if (match({TokenType::NUMBER, TokenType::STRING})) {
        return std::unique_ptr<Expr>(new Expr::Literal(previous().literal));
    }
    
    if (match({TokenType::SIGIL})) {
        Token identifier = consume(TokenType::IDENTIFIER, "Expect identifier after '$'.");
        return std::unique_ptr<Expr>(new Expr::Variable(identifier, true));
    } else if (match({TokenType::IDENTIFIER})) {
        return std::unique_ptr<Expr>(new Expr::Variable(previous(), false));
    }
    
    if (match({TokenType::LEFT_PAREN})) {
        std::unique_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
        return std::unique_ptr<Expr>(new Expr::Grouping(std::move(expr)));
    }
    
    throw error(peek(), "Expected expression.");
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    
    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::consume(TokenType type, std::string message) {
    if (check(type)) return advance();
    
    throw error(peek(), message);
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

Token Parser::peek() {
    return tokens.at(current);
}

Token Parser::previous() {
    return tokens.at(current - 1);
}

ParseError Parser::error(Token token, std::string message) {
    Log::error(token, message);
    return ParseError();
}

void Parser::synchronize() {
    advance();
    
    while (!isAtEnd()) {
        if (previous().type == TokenType::SEMICOLON || previous().type == TokenType::NEWLINE) return;
        
        switch (peek().type) {
            case TokenType::FN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
                return;
            default: break;
        }
        
        advance();
    }
}