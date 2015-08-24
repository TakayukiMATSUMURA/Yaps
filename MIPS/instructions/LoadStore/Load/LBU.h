/**
 * LBU.h
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

class LBU : public Load {
public:
    /// Default constructor
    LBU () : Load () {}
    LBU (const BinaryData& binary) : Load (binary) {}
    
    /// Destructor
    virtual ~LBU () {};
    
    std::string mnemonic () const override {return "lbu";}
    int opcode () const override {return ISA::LBU;}

    void loadFrom (IMemory* memory) override {
        result_ = memory->read(1, virtualAddress_).zeroExtension(32);
    }
};

namespace {

auto registerLbu = Decoder::instance()->registerInst<LBU>();

}

} // MIPS

} // Yaps
