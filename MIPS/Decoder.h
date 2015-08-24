/**
 * Decoder.h
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

#include <map>
#include <iostream>

#include "../lib/Singleton.h"

namespace Yaps {

namespace MIPS {

class Decoder : public Yaps::Decoder,
                public MyLibrary::Singleton<Decoder> {
    friend class MyLibrary::Singleton<Decoder>;
public:
    template <class T>
    bool registerInst() {
        BinaryData binaryTemplate = T().binaryTemplate();
        int identifier = getInstIdentifierFrom(binaryTemplate);
        
        return add(identifier,
                   CreatorUsingNew<T>::template create<const BinaryData&>);
    }
    
protected:
    virtual ~Decoder () {}

    int getInstIdentifierFrom (const BinaryData& binary) const override {
        auto op = (binary >> 26) & BinaryData::mask(6);
        auto regim = (binary >> 16) & BinaryData::mask(5);
        auto funct = binary & BinaryData::mask(6);

        int identifier = op << 11;
        if((op == ISA::SPECIAL) || (op == ISA::SPECIAL2)) {
            identifier |= funct;
        }
        else if(op == ISA::REGIMM) {
            identifier |= regim << 6;
        }
        return identifier;
    }
    
private:
    Decoder () {}

    static Decoder* create() {return new Decoder;}
    static void destroy(Decoder* decoder) {delete decoder;}
};

} // MIPS

} // Yaps
