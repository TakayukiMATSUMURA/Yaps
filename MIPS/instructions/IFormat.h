/**
 * IFormat.h
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

class IFormat : public Instruction {
public:
    /// Default constructor
    IFormat () : Instruction () {}
    IFormat (const BinaryData& binary) : Instruction(binary) {
        result_ = Operand(rt_.logicalRegisterNumber());
        imm_ = BinaryData(16, value());
    }
    /// Destructor
    virtual ~IFormat () {};
    
    virtual std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[result_.logicalRegisterNumber()] + ",";
        result += RegisterFile::nameAt[rt_.logicalRegisterNumber()] + ",";
        result += "0x" + imm_.toStringInHexadecimal(false);
        return result;
    }
    
protected:
    BinaryData imm_;
};

} // MIPS

} // Yaps

#include "IFormat/ADDI.h"
#include "IFormat/ADDIU.h"
#include "IFormat/ANDI.h"

#include "IFormat/ORI.h"

#include "IFormat/SLTI.h"
#include "IFormat/SLTIU.h"

#include "IFormat/TEQI.h"
#include "IFormat/TGEI.h"
#include "IFormat/TGEIU.h"
#include "IFormat/TGEU.h"
#include "IFormat/TLTI.h"
#include "IFormat/TLTIU.h"
#include "IFormat/TLTU.h"
#include "IFormat/TNEI.h"

#include "IFormat/XORI.h"
#include "IFormat/Branch.h"
