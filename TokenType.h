/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TokenType.h
 * Author: thewaffledimension
 *
 * Created on October 26, 2018, 12:50 PM
 */

#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum class TokenType {
    // Single character tokens
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, SEMICOLON, SLASH,
    QUESTION, COLON, SIGIL,
    LEFT_SQUARE, RIGHT_SQUARE,

    // One or two character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    PLUS, MINUS,
    STAR, EXPONENT,
    AND, OR, BIT_XOR,
    BIT_AND, BIT_OR,

    // Three character tokens
    SIGN, ELIPSIS,

    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    ELSE, ELSEIF, FALSE, FN, FOR, IF, IN, NIL,
    PRINT, RETURN, TRUE, VAR, WHILE,
    MODULE, IMPORT,

    INDENT, DEDENT, NEWLINE,

    END_OF_FILE
};

#endif /* TOKENTYPE_H */

