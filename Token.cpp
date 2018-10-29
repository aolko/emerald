/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Token.cpp
 * Author: thewaffledimension
 * 
 * Created on October 26, 2018, 12:51 PM
 */

#include "Token.h"

Token::Token() {
    type = TokenType::END_OF_FILE;
    lexeme = "";
    literal = NULL;
    line = 0;
    column = 0;
}

Token::Token(TokenType type, std::string lexeme, std::any literal, int line, int column)
 : type(type), lexeme(lexeme), literal(literal), line(line), column(column)
{
    
}

std::ostream& operator<<(std::ostream& os, const Token& tok) {
    os << TokenTypeNames[int(tok.type)] << " " << tok.lexeme << " " << tok.line << ":" << tok.column;
    return os;
}

