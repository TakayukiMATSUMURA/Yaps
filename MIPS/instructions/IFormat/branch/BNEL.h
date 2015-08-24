/**
 * BNEL.h
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

class BNEL : public BranchLikely {
public:
    /// Default constructor
    BNEL () : BranchLikely () {}
    BNEL (const BinaryData& binary) : BranchLikely(binary) {}
    
    /// Destructor
    virtual ~BNEL () {};
    
    void execute () override {
        nextPc_ = pc_ + (imm_.signExtension(32) << 2) + 4;
        isTaken_ = (rs_.value() != rt_.value());
    }
    
    std::string mnemonic () const override {return "bnel";}
    int opcode () const override {return ISA::BNEL;}
};

namespace {

auto registerBnel = Decoder::instance()->registerInst<BNEL>();

}

} // MIPS

} // Yaps
