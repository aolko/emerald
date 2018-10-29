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
#include "Token.h"
#include "Scanner.h"
/*
 * 
 */
int main(int argc, char** argv) {
    Scanner scanner = Scanner("if (i == 2):\n\tprint(\"Hello\")\n");
    std::vector<Token> tokens = scanner.scanTokens();
    
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i] << std::endl;
    }
    
    return 0;
}
