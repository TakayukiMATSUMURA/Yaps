/**
 * Operand.h
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

#include "RegisterFile.h"

namespace Yaps {

class Operand : public BinaryData {
public:
    Operand (int logicalRegisterNumber = -1, uint width = 32) :
        logicalRegisterNumber_(logicalRegisterNumber),
        physicalRegisterNumber_(logicalRegisterNumber),
        BinaryData(width) {
    }
    
    /// Destructor
    virtual ~Operand () {}
    
    Operand& operator= (const ulong& value) {
        static_cast<BinaryData&>(*this) = value;
        return *this;
    }
    
    void renameTo(int physicalRegisterNumber) {
        this->physicalRegisterNumber_ = physicalRegisterNumber;
    }
    
    void getValueFrom(RegisterFile* regFile) {
        static_cast<BinaryData&>(*this) =
            (*regFile)[physicalRegisterNumber_];
    }
    
    int logicalRegisterNumber () const {return logicalRegisterNumber_;}
    int physicalRegisterNumber () const {return physicalRegisterNumber_;}
    
private:
    int logicalRegisterNumber_;
    int physicalRegisterNumber_;
};

} // Yaps
