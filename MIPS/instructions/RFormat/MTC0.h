/**
 * MTC0.h
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

class MTC0 : public RFormat {
public:
    /// Default constructor
    MTC0 () : RFormat() {}
    MTC0 (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~MTC0 () {};

    void execute () override {
        result_ = rt_;
    }
    
    std::string mnemonic () const override {return "MTC0";}
    int opcode () const override {return ISA::COP0;}
};

namespace {

auto registerMtc0 = Decoder::instance()->registerInst<MTC0>();

}

} // MIPS

} // Yaps
