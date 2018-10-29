/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Log.h
 * Author: thewaffledimension
 *
 * Created on October 28, 2018, 4:18 PM
 */

#ifndef LOG_H
#define LOG_H

#include <vector>
#include <string>
#include "Token.h"
#include "Errors.h"

class Log {
public:
    Log();
    Log(const Log& orig);
    virtual ~Log();
    
    static void runtimeError(RuntimeError error);
    static void error(int line, std::string message);
    static void error(int line, int column, std::string message);
    static void error(int line, int column, std::string message, std::string lineStr);
    static void error(Token token, std::string message);
private:
    static std::vector<std::string> infos;
    static std::vector<std::string> warnings;
    static std::vector<std::string> errors;
    
    static void report(int line, int column, std::string where, std::string message, std::string lineStr);
};

#endif /* LOG_H */

