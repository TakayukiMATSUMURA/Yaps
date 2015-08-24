/**
 * Yaps.h
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
/**********************************************************************/
#include "./common/ALU.h"
#include "./common/ISA.h"
#include "./common/Decoder.h"
#include "./common/Operand.h"
#include "./common/BinaryData.h"
#include "./common/Instruction.h"
#include "./common/RegisterFile.h"
#include "./common/ProgramCounter.h"
#include "./common/PerformanceCounter.h"
#include "./common/SystemCallExecutor.h"

#include "./memory/IMemory.h"
#include "./memory/MainMemory.h"


#include "./loader/simloader.h"

#include "./Core/CPUCore.h"
#include "./Core/SingleCycleCore.h"
/**********************************************************************/
