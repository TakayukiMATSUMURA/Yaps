/**
 * SLL.h
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

class SLL : public RFormat {
public:
    /// Default constructor
    SLL () : RFormat () {}
    SLL (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~SLL () {}

    void execute () override {
        result_ = rt_ << shamt_;
    }
    
    std::string mnemonic () const override {
        if((rt_.logicalRegisterNumber() == 0) && (rd_.logicalRegisterNumber() == 0)) {
            if(shamt_ == 0)
                return "nop";
            else if(shamt_ == 1)
                return "ssnop";
        }
        return std::string("sll");
    }
    int opcode () const override {return ISA::SPECIAL;}
    int funct () const override {return ISA::SLL;}

    std::string toString () const override {
        if(mnemonic() == std::string("nop"))
            return std::string("nop");
        
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[result_.logicalRegisterNumber()] + ",";
        result += RegisterFile::nameAt[rt_.logicalRegisterNumber()] + ",";
        
        std::stringstream ss;
        BinaryData shamtData = BinaryData(5, shamt_);
        result += "0x" + shamtData.toStringInHexadecimal();
        
        return result;
    }
    
    bool isNop () const {
        return mnemonic() == std::string("nop");
    }
};

namespace {

auto registerSll = Decoder::instance()->registerInst<SLL>();

}

} // MIPS

} // Yaps
