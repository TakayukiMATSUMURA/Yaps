/**
 * Instruction.h
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

#include <string>
#include <cassert>
#include <iostream>

#include "Operand.h"
#include "RegisterFile.h"
#include "ProgramCounter.h"
#include "../Memory/IMemory.h"

namespace Yaps {

class Instruction : public BinaryData {
public:
    /// Default constructor
    Instruction () : BinaryData(32) {}
    
    Instruction (const BinaryData& binary) : BinaryData(32, binary) {}
    
    /// Destructor
    virtual ~Instruction () {};
    
    virtual void execute () {}
    
    virtual std::string mnemonic () const = 0;
    virtual int opcode () const = 0;
    virtual void fetchOperandsFrom (RegisterFile *) = 0;
    virtual void writeBackTo (RegisterFile *) = 0;
    
    virtual void loadFrom (IMemory *) {}
    virtual void storeTo (IMemory *) const {}
    
    virtual std::string toString () const = 0;

    virtual void setAddress (const ulong& pc) {
        assert(this->pc_ == 0);
        this->pc_ = pc;
    }
    
    ulong pc() const {return pc_;}
    
    ulong nextPc() const {return nextPc_;}
    
    bool isTaken () const {return isTaken_;}
    
    Operand result () const {return result_;}
    
    uint virtualAddress () const {return virtualAddress_;}
    
    virtual void update (ProgramCounter* pc) const {
        pc->increment();
    }
    
    virtual bool isNop () const {return false;}
    virtual bool isSystemCall () const {return false;}

    virtual BinaryData binaryTemplate() const = 0;
    
protected:
    ulong pc_ = 0;
    ulong nextPc_ = 0;;

    uint virtualAddress_ = 0;
    
    bool isTaken_ = false;

    Operand result_;
};

} // Yaps
