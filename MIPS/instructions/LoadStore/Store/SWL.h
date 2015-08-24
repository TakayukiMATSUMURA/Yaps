/**
 * SWL.h
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

class SWL : public Store {
public:
    /// Default constructor
    SWL () : Store() {}
    SWL (const BinaryData& binary) : Store(binary) {}
    
    /// Destructor
    virtual ~SWL () {};
    
    std::string mnemonic () const override {return "swl";}
    int opcode () const override {return ISA::SWL;}

    void storeTo (IMemory* memory) const override {
        BinaryData temp = BinaryData(32, memory->read(4, virtualAddress_ & ~0x3));
        
        int shamt = 24 - (virtualAddress_ & 0x3) * 8;
        ulong mask = BinaryData::mask(32) >> shamt;
        temp  = ((rt_ >> shamt) & mask) | (temp & ~mask);

        memory->write(virtualAddress_ & ~0x3, temp);
    }
};


namespace {

auto registerSwl = Decoder::instance()->registerInst<SWL>();

}

} // MIPS

} // Yaps
