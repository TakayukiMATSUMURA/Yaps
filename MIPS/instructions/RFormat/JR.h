/**
 * JR.h
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

class JR : public RFormat {
public:
    /// Default constructor
    JR () : RFormat () {}
    JR (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~JR () {}
    
    void execute () override {
        nextPc_ = rs_;
        isTaken_ = true;
    }
    
    std::string mnemonic () const override {return "jr";}
    int opcode () const override {return ISA::SPECIAL;}
    int funct () const override {return ISA::JR;}
    
    std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[rs_.logicalRegisterNumber()];
        return result;
    }
    
    void update (ProgramCounter* pc) const override {
        if(isTaken_) pc->setDelayPc(nextPc_);
        else pc->increment();
    }
};

namespace {

auto registerJr = Decoder::instance()->registerInst<JR>();

}

} // MIPS

} // Yaps
