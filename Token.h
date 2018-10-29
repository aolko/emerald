/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Token.h
 * Author: thewaffledimension
 *
 * Created on October 26, 2018, 12:51 PM
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <any>
#include <string>
#include <iostream>
#include "TokenType.h"

class Token {
public:
    Token();
    Token(TokenType type, std::string lexeme, std::any literal, int line, int column);
    
    TokenType type;
    std::string lexeme;
    std::any literal;
    int line;
    int column;
    
    friend std::ostream& operator<<(std::ostream& Str, const Token& tok);
private:
    
};

#endif /* TOKEN_H */

