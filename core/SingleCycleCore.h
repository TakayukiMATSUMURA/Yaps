/**
 * SingleCycleCore.h
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

#include "./CPUCore.h"

#include "../common/ALU.h"
#include "../common/Instruction.h"

namespace Yaps {

class SingleCycleCore : public CPUCore {
public:
    /// Default constructor
    SingleCycleCore(IMemory* memory) : CPUCore(memory) {
        alu_ = new ALU();
    }
    
    /// Destructor
    virtual ~SingleCycleCore() {
        delete alu_;
    }
    
    void driveWith (IMemory* memory) override {
        auto binary = memory->read(4, *programCounter_);
        instruction_ = decoder_->decode(binary);
        instruction_->setAddress(*programCounter_);
        instruction_->fetchOperandsFrom(registerFile_);
        
        alu_->execute(instruction_);
    }
    
    bool updateWith (IMemory* memory) override {
        instruction_->loadFrom(memory);
        instruction_->storeTo(memory);
        
        instruction_->writeBackTo(registerFile_);
        instruction_->update(programCounter_);
        
        performanceCounter_->get(instruction_);
        performanceCounter_->update();
        
        bool hasStopped = performanceCounter_->reachMaxCycle();
        if(instruction_->isSystemCall()) {
            hasStopped |= syscallExecutor_->execute(registerFile_, memory);
        }
        
        delete instruction_;
        
        return hasStopped;
    }
    
private:
    Instruction* instruction_;
    ALU* alu_;
};

} // Yaps
