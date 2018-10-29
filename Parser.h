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

#include <vector>
#include "Token.h"
#include "Stmt.h"
#include "Expr.h"

class Parser {
public:
    Parser();
private:
    std::vector<std::unique_ptr<Stmt>> statements;
};

#endif /* PARSER_H */

