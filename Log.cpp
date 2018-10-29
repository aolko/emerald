/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Log.cpp
 * Author: thewaffledimension
 * 
 * Created on October 28, 2018, 4:18 PM
 */

#include "Log.h"

Log::Log() {
}

Log::Log(const Log& orig) {
}

Log::~Log() {
}

void Log::runtimeError(std::exception error) {}
void Log::error(int line, std::string message) {
    report(line, 0, "", message, NULL);
}

void Log::error(int line, int column, std::string message) {
    report(line, column, "", message, NULL);
}

void Log::error(int line, int column, std::string message, std::string lineStr) {
    report(line, column, "", message, lineStr);
}

void Log::error(Token token, std::string message) {
    if (token.type == TokenType::END_OF_FILE) {
        report(token.line, token.column, " at end", message, NULL);
    } else {
        report(token.line, token.column, " at '" + token.lexeme + "'", message, NULL);
    }
}

void Log::report(int line, int column, std::string where, std::string message, std::string lineStr) {
    std::cout << "[" << line << ":" << column << "] Error" << where << ": " << message << std::endl;
}