/**
 * RegisterFile.h
 *
 * Copyright (C) 2015 Takayuki MATSUMURA
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * See LICENSE file on the base directory for more information.
 *
 */
/**********************************************************************/
#pragma once

#include <string>

#include "BinaryData.h"

namespace Yaps {

class RegisterFile {
public:
    RegisterFile (uint num) : NUMBER_OF_REGISTER(num) {
        reg_ = new BinaryData[NUMBER_OF_REGISTER];
        clear();
    }
    virtual ~RegisterFile () {
        delete[] reg_;
    }
    
    virtual BinaryData& operator[] (uint index) {
        return reg_[index];
    }
    
    virtual std::string toString () {
        std::string result = "RegisterFile\n";
        for(uint i = 0; i < NUMBER_OF_REGISTER; i++) {
            result += getStringIndex(i) + ":";
            result += reg_[i].toStringInHexadecimal() + "\n";
        }
        
        return result;
    }
    
    virtual std::string getStringIndex (int index) {
        std::stringstream ss;
        ss << std::setw(2) << index;
        return ss.str();
    }

    void clear () {
        for(uint i = 0; i < NUMBER_OF_REGISTER; i++) {
            reg_[i] = 0;
        }
    }
    
    const uint NUMBER_OF_REGISTER;
    
protected:
    BinaryData* reg_;
};

} // Yaps
