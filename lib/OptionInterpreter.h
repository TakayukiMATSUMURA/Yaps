/**
 * OptionInterpreter.h
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
#include <vector>
#include <functional>

namespace MyLibrary {

class OptionInterpreter {
    
public:
    using FunctionWithArgment = std::function<void(std::string)>;
    using FunctionWithoutArgment = std::function<void(void)>;
    
    bool add(std::string key,
             std::string usage,
             FunctionWithArgment func) {
        std::string keyWithDash = std::string("-") + key;
        
        auto it = functionsWithArgment_.find(keyWithDash);
        if(it != functionsWithArgment_.end()) return false;
        
        functionsWithArgment_[keyWithDash] = func;

        std::string usageWithDash = std::string(" ") + keyWithDash + usage;
        usages_.push_back(usageWithDash);
        
        return true;
    }
    bool add(std::string key,
             std::string usage,
             FunctionWithoutArgment func) {
        std::string keyWithDash = std::string("-") + key;
        
        auto it = functionsWithoutArgment_.find(keyWithDash);
        if(it != functionsWithoutArgment_.end()) return false;
        
        functionsWithoutArgment_[keyWithDash] = func;
        
        std::string usageWithDash = std::string(" ") + keyWithDash + usage;
        usages_.push_back(usageWithDash);
        
        return true;
    }
    
    virtual void analize(int argc, char *argv[]) {
        if(argc == 1) showUsages();
        
        for(int i = 1; i < argc; i++) {
            auto option = std::string(argv[i]);
            if(option[0] != '-') continue;
            
            auto func = functionsWithoutArgment_.find(option);
            if(func != functionsWithoutArgment_.end()) func->second();
            else {
                auto arg = ((i < argc - 1) && (argv[i + 1][0] != '-')) ?
                    std::string(argv[i + 1]) : "";
                if(arg == "") {
                    std::cout << "error: " << option
                              << " option needs any argument" << std::endl;
                    exit(0);
                }
                
                auto func = functionsWithArgment_.find(option);
                if(func == functionsWithArgment_.end()) {
                    std::cout << "error: " << option
                              << " is invalid option" << std::endl;
                    exit(0);
                }
                func->second(arg);
            }
        }
    }
    
    static void warning(std::string option, std::string arg) {
        std::cout << "\"" << arg << "\" is invalid argument "
                  << "for option \"-" << option << "\"" << std::endl;
    }
    
    virtual void showUsages() {
        std::cout << "usage" << std::endl;
        std::cout << "options" << std::endl;
        for(auto& usage : usages_)
            std::cout << usage << std::endl;
        
        exit(0);
    }
protected:
    /// Default constructor
    OptionInterpreter() {};
    /// Destructor
    virtual ~OptionInterpreter() {};
    
    std::map<std::string, FunctionWithArgment> functionsWithArgment_;
    std::map<std::string, FunctionWithoutArgment> functionsWithoutArgment_;
    std::vector<std::string> usages_;
};

} // MyLibrary
