/**
 * NOR.h
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

class NOR : public RFormat {
public:
    /// Default constructor
    NOR () : RFormat () {}
    NOR (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~NOR () {};
    
    void execute () override {
        result_ = ~(rs_ | rt_);
    }
    
    std::string mnemonic () const override {return "nor";}
    int opcode () const override {return ISA::SPECIAL;}
    int funct () const override {return ISA::NOR;}
};

namespace {

auto registerNor = Decoder::instance()->registerInst<NOR>();

}

} // MIPS

} // Yaps
