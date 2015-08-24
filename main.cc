/**
 * main.cc
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
#include <map>
#include <string>
#include <memory>
#include <iostream>

#include "./Yaps.h"
#include "./MIPS/MIPS.h"

using namespace Yaps;

int main(int argc, char *argv[]) {
    SystemConfigure::instance()->showIntroduction();
    SystemConfigure::instance()->analize(argc, argv);
    
    IMemory* memory = new MainMemory();
    CPUCore* CPU = new SingleCycleCore(memory);
    CPU->start();
    
    delete CPU;
    delete memory;
    
    return 0;
}
