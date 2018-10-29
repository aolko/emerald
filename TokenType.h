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

#define stringify( name ) # name

enum class TokenType {
    // Single character tokens
    LEFT_PAREN = 0, RIGHT_PAREN,
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

static const char* TokenTypeNames[] = {
    stringify( LEFT_PAREN ),
    stringify( RIGHT_PAREN ),
    stringify( LEFT_BRACE ),
    stringify( RIGHT_BRACE ),
    stringify( COMMA ),
    stringify( DOT ),
    stringify( SEMICOLON ),
    stringify( SLASH ),
    stringify( QUESTION ),
    stringify( COLON ),
    stringify( SIGIL ),
    stringify( LEFT_SQUARE ),
    stringify( RIGHT_SQUARE ),
    stringify( BANG ),
    stringify( BANG_EQUAL ),
    stringify( EQUAL ),
    stringify( EQUAL_EQUAL ),
    stringify( GREATER ),
    stringify( GREATER_EQUAL ),
    stringify( LESS ),
    stringify( LESS_EQUAL ),
    stringify( PLUS ),
    stringify( MINUS ),
    stringify( STAR ),
    stringify( EXPONENT ),
    stringify( AND ),
    stringify( OR ),
    stringify( BIT_XOR ),
    stringify( BIT_AND ),
    stringify( BIT_OR ),
    stringify( SIGN ),
    stringify( ELIPSIS ),
    stringify( IDENTIFIER ),
    stringify( STRING ),
    stringify( NUMBER ),
    stringify( ELSE ),
    stringify( ELSEIF ),
    stringify( FALSE ),
    stringify( FN ),
    stringify( FOR ),
    stringify( IF ),
    stringify( IN ),
    stringify( NIL ),
    stringify( PRINT ),
    stringify( RETURN ),
    stringify( TRUE ),
    stringify( VAR ),
    stringify( WHILE ),
    stringify( MODULE ),
    stringify( IMPORT ),
    stringify( INDENT ),
    stringify( DEDENT ),
    stringify( NEWLINE ),
    stringify( END_OF_FILE )
};

#endif /* TOKENTYPE_H */

