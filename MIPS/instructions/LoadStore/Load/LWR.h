/**
 * LWR.h
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

class LWR : public Load {
public:
    /// Default constructor
    LWR () : Load() {}
    LWR (const BinaryData& binary) : Load(binary) {}
    
    /// Destructor
    virtual ~LWR () {};
    
    std::string mnemonic () const override {return "lwr";}
    int opcode () const override {return ISA::LWR;}
    
    void loadFrom (IMemory* memory) override {
        auto temp = memory->read(4, virtualAddress_ & ~0x3);
        int shamt = (virtualAddress_ & 0x3) * 8;
        ulong mask = 0xffffffff >> shamt;
        result_  = (((temp >> shamt) & mask) | (rt_ & ~mask));
    }
};

namespace {

auto registerLwr = Decoder::instance()->Decoder::instance()->registerInst<LWR>();

}

} // MIPS

} // Yaps
