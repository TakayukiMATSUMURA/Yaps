/**
 * SystemConfigure.h
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
#include <limits>

#include "../loader/elf.h"
#include "../loader/simloader.h"

#include "../lib/Wrapper.h"
#include "../lib/Singleton.h"
#include "../lib/OptionInterpreter.h"

namespace Yaps {

using namespace MyLibrary;

class SystemConfigure : public OptionInterpreter,
                        public Singleton<SystemConfigure> {
    friend class Singleton<SystemConfigure>;
    
public:
    unsigned long long maxCycle () const {return maxCycle_;}
    unsigned long long skipCycle () const {return skipCycle_;}
    unsigned int debugMode () const {return debugMode_;}
    bool isInstructionMixMode () const {return  isInstructionMixMode_;}
    std::string binaryFileName () const {return binaryFileName_;}
    
    void showIntroduction () const {
        std::cout << "Yaps: Yet Another Processor Simulator" << std::endl;
    }

    void showUsages () override {
        std::cout << "usage: " << "Yaps [options] binaryFileName" << std::endl;
        std::cout << "options" << std::endl;
        for(auto& usage : usages_)
            std::cout << usage << std::endl;

        exit(0);
    }
    
    void analize (int argc, char *argv[]) override {
        OptionInterpreter::analize(argc, argv);
        
        for(int i = 1; i < argc; i++) {
            auto arg = std::string(argv[i]);
            
            std::ifstream ifs(arg);
            if(ifs.fail()) continue;
            
            if(binaryFileName_ != std::string("")) {
                std::cout << "multiple binary files" << std::endl;
                showUsages();
                exit(1);
            }
            binaryFileName_ = arg;
        }

        if(binaryFileName_ == std::string(""))
            showUsages();
    }
    
protected:

private:
    unsigned long long maxCycle_ = ULLONG_MAX;
    unsigned long long skipCycle_ = ULLONG_MAX;
    unsigned int debugMode_ = 0;
    bool isInstructionMixMode_ = false;
    std::string binaryFileName_ = "";
    
    /// Default constructor
    SystemConfigure () {
        auto maxCycleSetter = [&](std::string arg) { 
            auto maxCycle = calculatePostfix(arg);
            if(maxCycle == 0) OptionInterpreter::warning("e", arg);
            
            maxCycle_ = maxCycle;
        };
        add("e", " [num][kmg]: stop simulation after num cycles executed", maxCycleSetter);
        auto debugModeSetter = [&](std::string arg) {
            UInt value = arg;
            if((value < 1) || (value > 3)) OptionInterpreter::warning("d", arg);
            
            debugMode_ = value;
        };
        add("d",
            " 1: put the architectural state after simulation\n\
    2: put all the instructions executed", debugModeSetter);
            
        
        auto instructionMixModeSetter = [&]() {
            std::cout << "i mix mode." << std::endl;
            isInstructionMixMode_ = true;
        };
        add("i", ": put the instruction mix after simulation", instructionMixModeSetter);
    };
    
    /// Destructor
    virtual ~SystemConfigure () {};
    
    ULongLong calculatePostfix (std::string arg) {
        ULongLong valuePart = arg.substr(0, arg.size() - 1);
        if(valuePart == 0) return 0;
        
        ULongLong result = arg;
        if(arg.substr(arg.size() - 1) == "k") {
            ULongLong value = arg.substr(0, arg.size() - 1);
            result = value * 1000;
        }
        else if(arg.substr(arg.size() - 1) == "m") {
            ULongLong value = arg.substr(0, arg.size() - 1);
            result = value * 1000 * 1000;
        }
        else if(arg.substr(arg.size() - 1) == "g") {
            ULongLong value = arg.substr(0, arg.size() - 1);
            result = value * 1000 * 1000 * 1000;
        }
        return result;
    }

    static SystemConfigure* create() {return new SystemConfigure();}
    static void destroy(SystemConfigure* systemConfigure) {
        delete systemConfigure;
    }
};

} // Yaps
/**********************************************************************/
