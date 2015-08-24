/**
 * DIV.h
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

class DIV : public RFormat {
public:
    /// Default constructor
    DIV () : RFormat() {}
    DIV (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~DIV () {};

    void execute () override {
        if ((rt_ != 0) && ((rs_ != 0x80000000) || (rt_ != 0xffffffff))) {
            uint q = (uint) (rs_.signedValue() / rt_.signedValue());
            uint r = (uint) (rs_.signedValue() % rt_.signedValue());
            result64bit_ = (((ulong)r << 32) | q);
        } else {
            result64bit_ = 0;
        }
    }
    
    std::string mnemonic () const override {return "div";}
    int opcode () const override {return ISA::SPECIAL;}
    int funct () const override {return ISA::DIV;}
    
    void writeBackTo (Yaps::RegisterFile* regFile) override {
        (*regFile)[Yaps::MIPS::RegisterFile::HI] = BinaryData(32, result64bit_.value() >> 32);
        (*regFile)[Yaps::MIPS::RegisterFile::LO] = BinaryData(32, result64bit_);
    }
};


namespace {

auto registerDiv = Decoder::instance()->registerInst<DIV>();

}

} // MIPS

} // Yaps
