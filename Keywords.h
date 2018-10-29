/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Keywords.h
 * Author: thewaffledimension
 *
 * Created on October 28, 2018, 4:11 PM
 */

#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <map>
#include <string>
#include "TokenType.h"

static std::map<std::string, TokenType> keywords= {
    {"and", TokenType::AND},
    {"else", TokenType::ELSE},
    {"elsif", TokenType::ELSEIF},
    {"false", TokenType::FALSE},
    {"for", TokenType::FOR},
    {"fn", TokenType::FN},
    {"in", TokenType::IN},
    {"if", TokenType::IF},
    {"import", TokenType::IMPORT},
    {"nil", TokenType::NIL},
    {"or", TokenType::OR},
    {"print", TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"true", TokenType::TRUE},
    {"while", TokenType::WHILE}
};

#endif /* KEYWORDS_H */

