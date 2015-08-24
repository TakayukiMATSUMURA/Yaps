/**
 * JFormat.h
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

class JFormat : public Instruction {
public:
    /// Default constructor
    JFormat () : Instruction () {}
    JFormat (const BinaryData& binary) : Instruction(binary) {}
    /// Destructor
    virtual ~JFormat () {}
    
protected:
    BinaryData address_;

    void setAddress (const ulong& pc) override {
        Instruction::setAddress(pc);
        
        address_ = (pc_ & 0xf0000000) | (address() << 2);
    }
    
    virtual std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += address_.toStringSignedDecimal();
        return result;
    }
    
    void update (ProgramCounter* pc) const override {
        if(isTaken_) pc->setDelayPc(nextPc_);
        else pc->increment();
    }
};

} // MIPS

} // Yaps

#include "JFormat/J.h"
#include "JFormat/JAL.h"
