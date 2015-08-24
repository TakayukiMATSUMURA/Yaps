/**
 * PerformanceCounter.h
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

#include <sys/time.h>

#include "Instruction.h"
#include "../lib/Counter.h"

namespace Yaps {

class PerformanceCounter {
public:
    /// Default constructor
    PerformanceCounter() {
        imix_ = new Counter<std::string>();
        gettimeofday(&startTime_, nullptr);
    };
    /// Destructor
    virtual ~PerformanceCounter() {
        stopTimer();
        print();
        
        delete imix_;
    };
    
    void get (Instruction* instruction) {
        if(!instruction->isNop()) instCount_++;
        
        if(SystemConfigure::instance()->debugMode() == 2) {
            if(instruction->isNop()) std::cout << "[----------] ";
            else std::cout << "[" << std::setw(10) << instCount_ << "] ";
            
            std::cout << instruction->toString() << std::endl;
        }
        
        if(SystemConfigure::instance()->isInstructionMixMode())
            imix_->count(instruction->mnemonic());
    }
    
    void update () {
        cycleCount_++;
    }
    
    bool reachMaxCycle () const {
        return cycleCount_ >=  SystemConfigure::instance()->maxCycle();
    }
    
private:
    Counter<std::string>* imix_;

    unsigned long long instCount_ = 0;
    unsigned long long cycleCount_ = 0;
    
    struct timeval startTime_, endTime_;
    double simulationTime_ = 0;

    void stopTimer () {
        gettimeofday(&endTime_, nullptr);
        simulationTime_ = (endTime_.tv_sec - startTime_.tv_sec) +
            (endTime_.tv_usec - startTime_.tv_usec) * 1.0E-6;
    }
    
    double MIPS () const {
        return instCount_ / (simulationTime_ * 1000 * 1000);
    }
    
    void print () const {
        std::cout << "##### Simulation Results #####" << std::endl;
        std::cout << "inst count: " << instCount_ << std::endl;
        std::cout << "cycle count: " << cycleCount_ << std::endl;
        std::cout << "IPC: " << IPC() << std::endl;
        std::cout << "MIPS: " << MIPS() << std::endl;

        if(imix_->size() == 0) return;
        
        std::cout << imix_->toStringInDescendingOrder() << std::endl;
    }

    double IPC () const {
        return (double)instCount_ / (double)cycleCount_;
    }
};

} // Yaps
/**********************************************************************/
