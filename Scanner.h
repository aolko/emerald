/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scanner.h
 * Author: thewaffledimension
 *
 * Created on October 26, 2018, 12:50 PM
 */

#ifndef SCANNER_H
#define SCANNER_H

#include <any>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include "Token.h"
#include "Keywords.h"

class Scanner {
public:
    Scanner(std::string source);
    Scanner(const Scanner& orig);
    virtual ~Scanner();
    
    std::vector<Token> scanTokens();
private:
    std::string source;
    std::vector<Token> tokens = std::vector<Token>();
    int start = 0;
    int current = 0;
    int line = 0;
    int column = 0;
    int indent = 0;
    int altIndent = 0;
    std::stack<int> indents = std::stack<int>();
    std::stack<int> altIndents = std::stack<int>();
    std::stack<int> brackets = std::stack<int>();
    bool atbol = true;
    
    void scanToken();
    
    void string();
    void number();
    void identifier();
    
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    char advance();
    char previous();
    char peek();
    char peekNext();
    bool match(char expected);
    
    bool isAtEnd();
    
    void addToken(TokenType type);
    void addToken(TokenType type, std::any literal);
};

#endif /* SCANNER_H */

