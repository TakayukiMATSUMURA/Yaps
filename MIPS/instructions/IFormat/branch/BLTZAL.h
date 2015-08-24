/**
 * BLTZAL.h
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

namespace Yaps {

namespace MIPS {

class BLTZAL : public Branch {
public:
    /// Default constructor
    BLTZAL () : Branch() {}
    BLTZAL (const BinaryData& binary) : Branch(binary) {
        result_ = Operand(31);
    }
    
    /// Destructor
    virtual ~BLTZAL () {};
    
    void execute () override {
        nextPc_ = pc_ + (imm_.signExtension(32) << 2) + 4;
        isTaken_ = (rs_.signedValue() < 0);
        result_ = pc_ + 8;
    }
    
    std::string mnemonic () const override {return "bltzal";}
    int opcode () const override {return ISA::REGIMM;}
    int regimm () const override {return ISA::BLTZAL;}

    void writeBackTo (Yaps::RegisterFile* regFile) override {
        Instruction::writeBackTo(regFile);
    }
};

namespace {

auto registerBltzal = Decoder::instance()->registerInst<BLTZAL>();

}

} // MIPS

} // Yaps
