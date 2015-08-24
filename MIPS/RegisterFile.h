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

#include "../Memory/MainMemory.h"
#include "../common/RegisterFile.h"

namespace Yaps {

namespace MIPS {

class RegisterFile : public Yaps::RegisterFile {
public:
    /// Default constructor
    RegisterFile ();
    /// Destructor
    virtual ~RegisterFile ();
    
    virtual BinaryData& operator[] (uint index) override {
        reg_[0] = 0;
        return reg_[index];
    }
    virtual std::string getStringIndex (int index) override {
        return nameAt[index];
    }
    
    static const std::string nameAt[34];
    static const int HI = 32;
    static const int LO = 33;
};

} // MIPS

} // Yaps
