/**
 * LoadStore.h
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

#include "../Instruction.h"

namespace Yaps {

namespace MIPS {

class LoadStore : public IFormat {
public:
    /// Default constructor
    LoadStore () : IFormat () {}
    LoadStore (const BinaryData& binary) : IFormat(binary) {
        result_ = Operand(rt_.logicalRegisterNumber());
    }
    /// Destructor
    virtual ~LoadStore () {}
    
    void execute () override {
        virtualAddress_ = rs_ + imm_.signExtension(32);
        result_ = rt_;
    }
    
    virtual std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[result_.logicalRegisterNumber()] + ",";
        result += imm_.toStringSignedDecimal();
        
        result += "(" + RegisterFile::nameAt[rs_.logicalRegisterNumber()] + ")";
        return result;
    }
};

} // MIPS

} // Yaps

#include "LoadStore/Load.h"
#include "LoadStore/Store.h"
