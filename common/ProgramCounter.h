/**
 * ProgramCounter.h
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

#include <cassert>

#include "BinaryData.h"
#include "SystemConfigure.h"
#include "../loader/SimLoader.h"

namespace Yaps {

class ProgramCounter : public BinaryData {
public:
    ProgramCounter (uint width = 32) : BinaryData(width) {
        auto entryPoint = SimLoader::instance()->entryPoint();
        set(entryPoint);
        
        delayPc_ = 0;
    };
    
    /// Destructor
    virtual ~ProgramCounter () {};

    ProgramCounter& operator= (const BinaryData& obj) {
        static_cast<BinaryData>(*this) = obj;
        return *this;
    }
    
    virtual void increment () {
        if(delayPc_ == 0) {
            set(this->value() + 4);
            return;
        }            
        
        set(delayPc_);
        delayPc_ = 0;
    }
    
    virtual void incrementWithNoDelay () {
        delayPc_ = 0;
        set(this->value() + 8);
    }
    
    virtual void set (ulong next) override {
        assert((next % 4) == 0);
        BinaryData::set(next);
    }
    
    void setDelayPc (ulong nextPc) {
        this->increment();
        delayPc_ = nextPc;
    }
    
private:
    BinaryData delayPc_ = BinaryData(32);
};

} // Yaps
