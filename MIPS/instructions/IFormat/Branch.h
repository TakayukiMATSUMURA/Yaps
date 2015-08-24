/**
 * Branch.h
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

#include "../IFormat.h"

namespace Yaps {

namespace MIPS {

class Branch : public IFormat {
public:
    /// Default constructor
    Branch () : IFormat () {}
    Branch (const BinaryData& binary) : IFormat(binary) {}
    /// Destructor    
    virtual ~Branch () {}
    
    virtual std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[rt_.logicalRegisterNumber()] + ",";
        std::stringstream ss;
        int immediate = imm_;
        ss << immediate;
        result += ss.str();
        return result;
    }
    
    void update (ProgramCounter* pc) const override {
        if(isTaken_) pc->setDelayPc(nextPc_);
        else pc->increment();
    }
    void writeBackTo (Yaps::RegisterFile*) override {}
};

class BranchLikely : public Branch {
public:
    /// Default constructor
    BranchLikely () : Branch () {}
    BranchLikely (const BinaryData& binary) : Branch(binary) {
        result_ = Operand();
    }
    /// Destructor
    virtual ~BranchLikely () {}
    
    void update (ProgramCounter* pc) const override {
        if(isTaken_) pc->setDelayPc(nextPc_);
        else pc->incrementWithNoDelay();
    }
};

} // MIPS

} // Yaps

#include "Branch/BEQ.h"
#include "Branch/BGEZ.h"
#include "Branch/BGEZAL.h"
#include "Branch/BGEZALL.h"
#include "Branch/BGTZ.h"
#include "Branch/BLEZ.h"
#include "Branch/BLTZ.h"
#include "Branch/BLTZAL.h"
#include "Branch/BNE.h"

//likely
#include "Branch/BEQL.h"
#include "Branch/BGEZL.h"
#include "Branch/BGTZL.h"
#include "Branch/BLEZL.h"
#include "Branch/BLTZALL.h"
#include "Branch/BLTZL.h"
#include "Branch/BNEL.h"
