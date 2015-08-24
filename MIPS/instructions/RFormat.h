/**
 * RFormat.h
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

class RFormat : public Instruction {
public:
    /// Default constructor
    RFormat () : Instruction () {}
    RFormat (const BinaryData& binary) : Instruction(binary) {
        result_ = Operand(rd_.logicalRegisterNumber());
    }
    /// Destructor
    virtual ~RFormat () {};
    
    virtual std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[result_.logicalRegisterNumber()] + ",";
        result += RegisterFile::nameAt[rs_.logicalRegisterNumber()] + ",";
        result += RegisterFile::nameAt[rt_.logicalRegisterNumber()];
        return result;
    }
};

} // MIPS

} // Yaps

#include "RFormat/ADD.h"
#include "RFormat/ADDU.h"
#include "RFormat/AND.h"

#include "RFormat/CFC0.h"
#include "RFormat/CLO.h"
#include "RFormat/CLZ.h"

#include "RFormat/DIV.h"
#include "RFormat/DIVU.h"

#include "RFormat/JALR.h"
#include "RFormat/JR.h"

#include "RFormat/MADD.h"
#include "RFormat/MADDU.h"
#include "RFormat/MFC0.h"
#include "RFormat/MFHI.h"
#include "RFormat/MFLO.h"
#include "RFormat/MOVN.h"
#include "RFormat/MOVZ.h"
#include "RFormat/MSUB.h"
#include "RFormat/MSUBU.h"
#include "RFormat/MTC0.h"
#include "RFormat/MTHI.h"
#include "RFormat/MTLO.h"
#include "RFormat/MUL.h"
#include "RFormat/MULT.h"
#include "RFormat/MULTU.h"

#include "RFormat/NOR.h"

#include "RFormat/OR.h"

#include "RFormat/SLL.h"
#include "RFormat/SLLV.h"
#include "RFormat/SLT.h"
#include "RFormat/SLTU.h"

#include "RFormat/SRA.h"
#include "RFormat/SRAV.h"
#include "RFormat/SRL.h"
#include "RFormat/SRLV.h"
#include "RFormat/SUB.h"
#include "RFormat/SUBU.h"

#include "RFormat/TEQ.h"

#include "RFormat/XOR.h"
