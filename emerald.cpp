/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   emerald.cpp
 * Author: thewaffledimension
 *
 * Created on October 26, 2018, 12:49 PM
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include <memory>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "File.h"

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc == 2) {
        std::string file = argv[1];
        std::string source = File::readFile(file);
        
        Scanner scanner = Scanner(source);
        std::vector<Token> tokens = scanner.scanTokens();

        for (int i = 0; i < tokens.size(); i++) {
            std::cout << tokens[i] << std::endl;
        }

        Parser parser(tokens);
        std::vector<std::unique_ptr<Stmt>> stmts = std::move(parser.parse());
    }
    
    return 0;
}

