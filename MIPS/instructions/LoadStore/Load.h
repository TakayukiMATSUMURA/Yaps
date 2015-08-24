/**
 * Load.h
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

#include "../LoadStore.h"

namespace Yaps {

namespace MIPS {

class Load : public LoadStore {
public:
    /// Default constructor
    Load () : LoadStore () {}
    Load (const BinaryData& binary) : LoadStore(binary) {}
    
    /// Destructor
    virtual ~Load () {}
};

} // MIPS

} // Yaps

#include "Load/LB.h"
#include "Load/LBU.h"
#include "Load/LH.h"
#include "Load/LHU.h"
#include "Load/LUI.h"
#include "Load/LW.h"
#include "Load/LWL.h"
#include "Load/LWR.h"
