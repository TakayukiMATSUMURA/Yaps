/**
 * MSUB.h
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

class MSUB : public RFormat {
public:
    /// Default constructor
    MSUB () : RFormat() {}
    MSUB (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~MSUB () {};
    
    void execute () override {
        signed long long temp = (hi_.signedValue() << 32) | lo_;
        temp = temp - (signed long long)rs_ * (signed long long)rt_;
        result64bit_ = static_cast<ulong>(temp);
    }
    
    std::string mnemonic () const override {return "msub";}
    int opcode () const override {return ISA::SPECIAL2;}
    int funct () const override {return ISA::MSUB;}

    void writeBackTo (Yaps::RegisterFile* regFile) override {
        (*regFile)[Yaps::MIPS::RegisterFile::HI] = BinaryData(32, result64bit_.value() >> 32);
        (*regFile)[Yaps::MIPS::RegisterFile::LO] = BinaryData(32, result64bit_);
    }
};

namespace {

auto registerMsub = Decoder::instance()->registerInst<MSUB>();

}

} // MIPS

} // Yaps
