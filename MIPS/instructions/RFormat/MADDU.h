/**
 * MADDU.h
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

class MADDU : public RFormat {
public:
    /// Default constructor
    MADDU () : RFormat() {}
    MADDU (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~MADDU () {};
    
    void execute () override {
        auto temp = hi_ << 32 | lo_;
        result64bit_ = temp + rs_ * rt_;
    }
    
    std::string mnemonic () const override {return "maddu";}
    int opcode () const override {return ISA::SPECIAL2;}
    int funct () const override {return ISA::MADDU;}
    
    void writeBackTo (Yaps::RegisterFile* regFile) override {
        (*regFile)[Yaps::MIPS::RegisterFile::HI] = BinaryData(32, result64bit_.value() >> 32);
        (*regFile)[Yaps::MIPS::RegisterFile::LO] = BinaryData(32, result64bit_);
    }
};

namespace {

auto registerMaddu = Decoder::instance()->registerInst<MADDU>();

}

} // MIPS

} // Yaps
