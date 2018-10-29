/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Util.h
 * Author: thewaffledimension
 *
 * Created on October 29, 2018, 12:03 AM
 */

#ifndef UTIL_H
#define UTIL_H

#include <memory>

namespace Util {
    template<typename Base, typename T>
    inline bool instanceof(const T *ptr) {
        return dynamic_cast<const Base*>(ptr) != NULL;
    }
}

#endif /* UTIL_H */

