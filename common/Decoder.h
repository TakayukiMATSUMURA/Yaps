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

#include "Instruction.h"
#include "../lib/Factory.h"

namespace Yaps {

class IDecoder {
public:
    /// Destructor
    virtual ~IDecoder () {};
    
    virtual Instruction* decode (const BinaryData&) = 0;
};

class Decoder : public IDecoder,
                public MyLibrary::Factory<Instruction, int,
                       std::function<Instruction*(const BinaryData&)>> {
public:
    Instruction* decode (const BinaryData& binary) override {
        auto identifier = getInstIdentifierFrom(binary);
        return this->createFrom(identifier, binary);
    }
    
protected:
    virtual int getInstIdentifierFrom (const BinaryData&) const = 0;
};

} // Yaps
