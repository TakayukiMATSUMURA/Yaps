/**
 * MainMemory.h
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

#include "./IMemory.h"

namespace Yaps {

class MainMemory : public IMemory {
public:
    /// Default constructor
    MainMemory(int size = DEFAULT_MEMORY_SIZE) : size_(size) {
        table_ = new unsigned char[size_];
        for(int i = 0; i < size_; i++)
            table_[i] = 0;
        
        for(int i = 0; i < SimLoader::instance()->theNumberOfMemoryTable(); i++)
            write(SimLoader::instance()->memoryTable()[i].addr, BinaryData(8, SimLoader::instance()->memoryTable()[i].data));
    }
    
    /// Destructor
    virtual ~MainMemory() {};

    void write (uint address, BinaryData data) override {
        uint byte = data.width() / 8;
        for(uint i = 0; i < byte; i++)
            table_[address + i] = data.byte(i);
    }
    
    BinaryData read (uint byte, uint address) override {
        BinaryData result = BinaryData(byte * 8);
        for(uint i = 0; i < byte; i++)
            result = result | (table_[address + i] << (i * 8));
        
        return result;
    }
    
    const static int DEFAULT_MEMORY_SIZE = 0x8000000;
    
protected:

private:
    unsigned char* table_;
    const int size_ = -1;
};

} // Yaps
