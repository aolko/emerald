/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Errors.h
 * Author: thewaffledimension
 *
 * Created on October 28, 2018, 11:20 PM
 */

#ifndef ERRORS_H
#define ERRORS_H

#include <string>

class ParseError : public std::exception {
    ParseError() {};
};

class RuntimeError : public std::runtime_error {
    RuntimeError(std::string message) : std::runtime_error(message) {};
};

#endif /* ERRORS_H */

