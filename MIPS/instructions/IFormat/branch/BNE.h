/**
 * BNE.h
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

class BNE : public Branch {
public:
    /// Default constructor
    BNE () : Branch () {}
    BNE (const BinaryData& binary) : Branch(binary) {}
    
    /// Destructor
    virtual ~BNE () {};

    void execute () override {
        nextPc_ = pc_ + (imm_.signExtension(32) << 2) + 4;
        isTaken_ = (rs_ != rt_);
    }
    
    std::string mnemonic () const override {return "bne";}
    int opcode () const override {return ISA::BNE;}
};

namespace {

auto registerBne = Decoder::instance()->registerInst<BNE>();

}

} // MIPS

} // Yaps
