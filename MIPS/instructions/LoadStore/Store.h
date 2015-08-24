/**
 * Store.h
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

class Store : public LoadStore {
public:
    /// Default constructor
    Store () : LoadStore () {}
    Store (const BinaryData& binary) : LoadStore(binary) {}
    
    /// Destructor
    virtual ~Store () {}
    
    void writeBackTo (Yaps::RegisterFile*) override {}
};

} // MIPS

} // Yaps

#include "Store/SB.h"
#include "Store/SH.h"
#include "Store/SW.h"
#include "Store/SWL.h"
#include "Store/SWR.h"
