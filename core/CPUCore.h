/**
 * CPUCore.h
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
#include <string>
#include <iostream>
#include <sys/time.h>

#include "../common/ISA.h"
#include "../common/Decoder.h"
#include "../common/RegisterFile.h"
#include "../common/ProgramCounter.h"
#include "../common/SystemConfigure.h"
#include "../common/PerformanceCounter.h"
#include "../common/SystemCallExecutor.h"

#include "../memory/IMemory.h"

namespace Yaps {

class CPUCore {
public:
    /// Default constructor
    CPUCore(IMemory* memory) : memory_(memory) {
        programCounter_ = new ProgramCounter();
        
        auto ISACode = SimLoader::instance()->archtype;
        const auto isa = ISA::getFactoryFrom(ISACode);
        decoder_ = isa->create<IDecoder>();
        registerFile_ = isa->create<RegisterFile>();
        syscallExecutor_ = isa->create<SystemCallExecutor>();
        delete isa;
        
        performanceCounter_ = new PerformanceCounter();
    }
    
    /// Destructor
    virtual ~CPUCore() {
        if(SystemConfigure::instance()->debugMode() == 1)
            std::cout << registerFile_->toString() << std::endl;
        
        delete programCounter_;
        delete decoder_;
        delete registerFile_;
        delete syscallExecutor_;
        delete performanceCounter_;
    }
    
    void start () {
        for(unsigned long long i = 0;i < SystemConfigure::instance()->maxCycle();i++) {
            driveWith(memory_);
            bool CPUHasStopped = updateWith(memory_);
            if(CPUHasStopped) break;
        }
    }
    
    virtual void driveWith (IMemory* memory) = 0;
    virtual bool updateWith (IMemory* memory) = 0;
    
protected:
    ProgramCounter* programCounter_;
    IDecoder* decoder_;
    RegisterFile* registerFile_;
    SystemCallExecutor* syscallExecutor_;
    
    PerformanceCounter* performanceCounter_;

    IMemory* memory_;
};

} // Yaps
