/**
 * SWR.h
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

class SWR : public Store {
public:
    /// Default constructor
    SWR () : Store() {}
    SWR (const BinaryData& binary) : Store(binary) {}
    
    /// Destructor
    virtual ~SWR () {};
    
    std::string mnemonic () const override {return "swr";}
    int opcode () const override {return ISA::SWR;}

    void storeTo (IMemory* memory) const override {
        BinaryData temp = BinaryData(32, memory->read(4, virtualAddress_ & ~0x3));
        
        int shamt = (virtualAddress_ & 0x3) * 8;
        ulong mask = BinaryData::mask(32) << shamt;
        temp  = (((rt_ << shamt) & mask) | (temp & ~mask));

        memory->write(virtualAddress_ & ~0x3, temp);
    }
};

namespace {

auto registerSwr = Decoder::instance()->registerInst<SWR>();

}

} // MIPS

} // Yaps
