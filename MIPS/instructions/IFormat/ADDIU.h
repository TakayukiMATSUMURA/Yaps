/**
 * ADDIU.h
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

class ADDIU : public IFormat {
public:
    /// Default constructor
    ADDIU () : IFormat () {}
    ADDIU (const BinaryData& binary) : IFormat(binary) {}
    
    /// Destructor
    virtual ~ADDIU () {};
    
    void execute () override {
        result_ = rs_ + imm_.signExtension(32);
    }
    
    std::string mnemonic () const override {return "addiu";}
    int opcode () const override {return ISA::ADDIU;}
    
    std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[result_.logicalRegisterNumber()] + ",";
        result += RegisterFile::nameAt[rs_.logicalRegisterNumber()] + ",";
        result += imm_.toStringSignedDecimal();
        return result;
    }
};

namespace {

auto registerAddiu = Decoder::instance()->registerInst<ADDIU>();

}

} // MIPS

} // Yaps
