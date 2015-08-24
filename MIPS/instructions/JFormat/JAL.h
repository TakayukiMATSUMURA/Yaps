/**
 * JAL.h
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

class JAL : public JFormat {
public:
    /// Default constructor
    JAL () : JFormat() {}
    JAL (const BinaryData& binary) : JFormat(binary) {
        result_ = Yaps::Operand(31);
    }
    
    /// Destructor
    virtual ~JAL () {};
    
    void execute () override {
        nextPc_ = address_;
        isTaken_ = true;
        result_ = pc_ + 8;
    }
    
    std::string mnemonic () const override {return "jal";}
    int opcode () const override {return ISA::JAL;}
};

namespace {

auto registerJal = Decoder::instance()->registerInst<JAL>();

}

} // MIPS

} // Yaps
