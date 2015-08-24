/**
 * RegisterFile.cc
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
#include "./RegisterFile.h"

namespace Yaps {

namespace MIPS {

const std::string RegisterFile::nameAt[34] = {
    "$zr",
    "$at",
    
    "$v0",
    "$v1",
    
    "$a0",
    "$a1",
    "$a2",
    "$a3",
    
    "$t0",
    "$t1",
    "$t2",
    "$t3",
    "$t4",
    "$t5",
    "$t6",
    "$t7",
    
    "$s0",
    "$s1",
    "$s2",
    "$s3",
    "$s4",
    "$s5",
    "$s6",
    "$s7",
    
    "$t8",
    "$t9",
    
    "$k0",
    "$k1",
    
    "$gp",
    "$sp",
    "$fp",
    "$ra",
    
    "$Hi",
    "$Lo"
};

/**
 * Default constructor
 */
RegisterFile::RegisterFile() : Yaps::RegisterFile (34) {
    auto stackPointer = SimLoader::instance()->stackPointer();
    
    reg_[29] = (stackPointer != 0) ? stackPointer :
        (MainMemory::DEFAULT_MEMORY_SIZE - 0x100);
    
    reg_[25] = SimLoader::instance()->entryPoint();
}
/**
 * Default destructor
 */
RegisterFile::~RegisterFile() {
}

} // MIPS

} // Yaps
