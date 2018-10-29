/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.h
 * Author: thewaffledimension
 *
 * Created on October 29, 2018, 1:11 PM
 */

#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include "Log.h"

namespace File {
    std::string readFile(std::string path) {
        std::string line;
        std::ifstream file(path);
        
        std::string contents = "";
        
        if (file.is_open()) {
            while (std::getline(file, line)) {
                contents += line + '\n';
            }
            
            file.close();
        } else {
            Log::error(0, "Unable to open file '" + path + "'.");
        }
        
        return contents;
    }
};

#endif /* FILE_H */

