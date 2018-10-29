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
        std::unique_ptr<Stmt> stmt = declaration();
        if (stmt)
            statements.push_back(std::move(stmt));
    }
    
    return statements;
}

std::unique_ptr<Stmt> Parser::declaration() {
    try {
        if (match({TokenType::IDENTIFIER})) return varDeclaration();
        if (match({TokenType::SIGIL})) return globalVarDeclaration();
        
        return statement();
    } catch (ParseError error) {
        synchronize();
        return nullptr;
    }
}

std::unique_ptr<Stmt> Parser::varDeclaration() {
    
}

std::unique_ptr<Stmt> Parser::globalVarDeclaration() {
    
}

std::unique_ptr<Stmt> Parser::statement() {
    
}

std::unique_ptr<Stmt> Parser::ifStatement() {
    
}

std::vector<std::unique_ptr<Stmt>> Parser::block() {
    
}

std::unique_ptr<Stmt> Parser::expressionStatement() {
    
}

std::unique_ptr<Expr> Parser::expression() {
    
}

std::unique_ptr<Expr> Parser::assignment() {
    
}

std::unique_ptr<Expr> Parser::bitwise() {
    
}

std::unique_ptr<Expr> Parser::logical() {
    
}

std::unique_ptr<Expr> Parser::equality() {
    
}

std::unique_ptr<Expr> Parser::comparison() {
    
}

std::unique_ptr<Expr> Parser::addition() {
    
}

std::unique_ptr<Expr> Parser::multiplication() {
    
}

std::unique_ptr<Expr> Parser::unary() {
    
}

std::unique_ptr<Expr> Parser::primary() {
    
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