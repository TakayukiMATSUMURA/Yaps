/**
 * MSUBU.h
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

class MSUBU : public RFormat {
public:
    /// Default constructor
    MSUBU () : RFormat() {}
    MSUBU (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~MSUBU () {};
    
    void execute () override {
        long temp = (hi_ << 32) | lo_;
        temp =  temp - rs_ * rt_;
        result64bit_ = temp;
    }
    
    std::string mnemonic () const override {return "msubu";}
    int opcode () const override {return ISA::SPECIAL2;}
    int funct () const override {return ISA::MSUBU;}

    void writeBackTo (Yaps::RegisterFile* regFile) override {
        (*regFile)[Yaps::MIPS::RegisterFile::HI] = BinaryData(32, result64bit_.value() >> 32);
        (*regFile)[Yaps::MIPS::RegisterFile::LO] = BinaryData(32, result64bit_);
    }
};

namespace {

auto registerMsubu = Decoder::instance()->registerInst<MSUBU>();

}

} // MIPS

} // Yaps
