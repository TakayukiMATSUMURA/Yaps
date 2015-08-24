/**
 * SRA.h
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

class SRA : public RFormat {
public:
    /// Default constructor
    SRA () : RFormat () {}
    SRA (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~SRA () {}

    void execute () override {
        result_ = rt_.shiftRightArithmetic(shamt_);
    }
    
    std::string mnemonic () const override {return "sra";}
    int opcode () const override {return ISA::SPECIAL;}
    int funct () const override {return ISA::SRA;}
    
    std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[result_.logicalRegisterNumber()] + ",";
        result += RegisterFile::nameAt[rt_.logicalRegisterNumber()] + ",";
        
        BinaryData shamtData = BinaryData(32, shamt_);
        result += "0x" + shamtData.toStringInHexadecimal(false);
        return result;
    }
};

namespace {

auto registerSra = Decoder::instance()->registerInst<SRA>();

}

} // MIPS

} // Yaps
