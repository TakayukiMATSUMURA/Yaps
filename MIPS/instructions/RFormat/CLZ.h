/**
 * CLZ.h
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

class CLZ : public RFormat {
public:
    /// Default constructor
    CLZ () : RFormat() {}
    CLZ (const BinaryData& binary) : RFormat(binary) {}
    
    /// Destructor
    virtual ~CLZ () {};
    
    void execute () override {
        for(result_ = 0; result_ < 32; result_ = result_ + 1)
            if (rs_ & (0x80000000u >> result_))
                break;
    }
    
    std::string mnemonic () const override {return "clz";}
    int opcode () const override {return ISA::SPECIAL2;}
    int funct () const override {return ISA::CLZ;}
};

namespace {

auto registerClz = Decoder::instance()->registerInst<CLZ>();

}

} // MIPS

} // Yaps
