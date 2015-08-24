/**
 * SRL.h
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

class SRL : public RFormat {
public:
    /// Default constructor
    SRL () : RFormat() {}
    SRL (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~SRL () {}
    
    void execute () override {
        result_ = rt_ >> shamt_;
    }
    
    std::string mnemonic () const override {return "srl";}
    int opcode () const override {return ISA::SPECIAL;}
    int funct () const override {return ISA::SRL;}
    
    std::string toString () const override {
        std::string result = "";
        result += (mnemonic() + "  ");
        result += RegisterFile::nameAt[result_.logicalRegisterNumber()] + ",";
        result += RegisterFile::nameAt[rt_.logicalRegisterNumber()] + ",";
        
        std::stringstream ss;
        ss << shamt_.value();
        result += "0x" + ss.str();
        return result;
    }
};


namespace {

auto registerSrl = Decoder::instance()->registerInst<SRL>();

}

} // MIPS

} // Yaps
