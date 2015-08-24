/**
 * SLTIU.h
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

class SLTIU : public IFormat {
public:
    /// Default constructor
    SLTIU () : IFormat () {}
    SLTIU (const BinaryData& binary) : IFormat(binary) {}
    
    /// Destructor
    virtual ~SLTIU () {};
    
    void execute () override {
        result_ = (rs_ < imm_.signExtension(32)) ? 1 : 0;
    }
    
    std::string mnemonic () const override {return "sltiu";}
    int opcode () const override {return ISA::SLTIU;}
    
    std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[result_.logicalRegisterNumber()] + ",";
        result += RegisterFile::nameAt[rt_.logicalRegisterNumber()] + ",";
        result += imm_.toStringInHexadecimal(false);
        return result;
    }
};

namespace {

auto registerSltiu = Decoder::instance()->registerInst<SLTIU>();

}

} // MIPS

} // Yaps
