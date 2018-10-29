/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: thewaffledimension
 *
 * Created on October 28, 2018, 10:18 PM
 */

#ifndef PARSER_H
#define PARSER_H

#include <tuple>
#include <string>
#include <vector>
#include <memory>
#include "Token.h"
#include "Stmt.h"
#include "Expr.h"
#include "Errors.h"

class Parser {
public:
    Parser(std::vector<Token> tokens);
    
    std::vector<std::unique_ptr<Stmt>> parse();
private:
    std::unique_ptr<Stmt> declaration();
    std::unique_ptr<Stmt> varDeclaration();
    std::unique_ptr<Stmt> globalVarDeclaration();
    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> ifStatement();
    std::vector<std::unique_ptr<Stmt>> block();
    std::unique_ptr<Stmt> expressionStatement();
    
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> assignment();
    std::unique_ptr<Expr> bitwise();
    std::unique_ptr<Expr> logical();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> addition();
    std::unique_ptr<Expr> multiplication();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();
    
    template <typename... Args>
    bool match(TokenType type1, Args... args);
    bool check(TokenType type);
    Token advance();
    Token consume(TokenType type, std::string message);
    bool isAtEnd();
    Token peek();
    Token previous();
    
    ParseError error(Token token, std::string message);
    
    void synchronize();
    
    std::vector<std::unique_ptr<Stmt>> statements;
    std::vector<Token> tokens;
};

#endif /* PARSER_H */

