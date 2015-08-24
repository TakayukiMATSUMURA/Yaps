/**
 * LHU.h
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

class LHU : public Load {
public:
    /// Default constructor
    LHU () : Load () {}
    LHU (const BinaryData& binary) : Load(binary) {}
    
    /// Destructor
    virtual ~LHU () {};
    
    std::string mnemonic () const override {return "lhu";}
    int opcode () const override {return ISA::LHU;}

    void loadFrom (IMemory* memory) override {
        result_ = memory->read(2, virtualAddress_).zeroExtension(32);
    }
};

namespace {

auto registerLhu = Decoder::instance()->registerInst<LHU>();

}

} // MIPS

} // Yaps
