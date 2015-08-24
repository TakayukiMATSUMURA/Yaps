/**
 * Instruction.h
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

#include "../common/Operand.h"
#include "../common/Instruction.h"

#include "./Decoder.h"
#include "./RegisterFile.h"

namespace Yaps {

namespace MIPS {

class Instruction : public Yaps::Instruction {
public:
    /// Default constructor
    Instruction () {};
    Instruction (const BinaryData& binary) : Yaps::Instruction(binary) {
        rs_ = Operand((value() >> 21) & BinaryData::mask(5));
        rt_ = Operand((value() >> 16) & BinaryData::mask(5));
        rd_ = Operand((value() >> 11) & BinaryData::mask(5));
        hi_ = Operand(RegisterFile::HI);
        lo_ = Operand(RegisterFile::LO);
        
        shamt_ = (value() >> 6) & BinaryData::mask(5);
    }
    // Destructor
    virtual ~Instruction () {};
    
    virtual std::string mnemonic () const = 0;
    virtual int opcode () const = 0;
    
    void fetchOperandsFrom (Yaps::RegisterFile* regFile) override {
        rs_.getValueFrom(regFile);
        rt_.getValueFrom(regFile);
        rd_.getValueFrom(regFile);
        hi_.getValueFrom(regFile);
        lo_.getValueFrom(regFile);
    }
    
    void writeBackTo (Yaps::RegisterFile* regFile) override {
        if(result_.logicalRegisterNumber() > 0)
            (*regFile)[result_.physicalRegisterNumber()] = result_;
    }
    
    virtual int funct () const {return 0;}
    virtual int regimm () const {return 0;}
    
    virtual std::string toString () const override {
        return mnemonic();
    }
    
    BinaryData binaryTemplate() const override {
        return BinaryData(32, (opcode() << 26) | (regimm() << 16) | funct());
    }
    
    BinaryData result64bit () const {return result64bit_;}
    
protected:
    Operand rs_;
    Operand rt_;
    Operand rd_;
    Operand hi_;
    Operand lo_;
    
    Operand shamt_;
    
    BinaryData result64bit_ = BinaryData(64);
    
    BinaryData address () const {
        return BinaryData(26, value() & BinaryData::mask(26));
    }
};
/// stream output operator
std::ostream& operator<<(std::ostream& lhs, const Instruction& rhs) {
    lhs << rhs.toString();
    return lhs;
}

} // MIPS

} // Yaps

#include "instructions/others/SYSCALL.h"

#include "instructions/RFormat.h"
#include "instructions/IFormat.h"
#include "instructions/LoadStore.h"
#include "instructions/JFormat.h"

