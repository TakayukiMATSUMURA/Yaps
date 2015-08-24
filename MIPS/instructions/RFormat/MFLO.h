/**
 * MFLO.h
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

class MFLO : public RFormat {
public:
    /// Default constructor
    MFLO () : RFormat () {}
    MFLO (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~MFLO () {}
    
    void execute () override {
        result_ = static_cast<ulong>(lo_);
    }
    
    std::string mnemonic () const override {return "mflo";}
    int opcode () const override {return ISA::SPECIAL;}
    int funct () const override {return ISA::MFLO;}
};

namespace {

auto registerMflo = Decoder::instance()->registerInst<MFLO>();

}

} // MIPS

} // Yaps
