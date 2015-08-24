/**
 * IMemory.h
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

#include "../loader/simloader.h"
#include "../common/BinaryData.h"
#include "../common/SystemConfigure.h"

namespace Yaps {

class IMemory {
public:
    /// Default constructor
    IMemory() {}
    
    /// Destructor
    virtual ~IMemory() {};
    
    virtual void write (uint, BinaryData) = 0;
    virtual BinaryData read (uint, uint) = 0;
    
protected:

private:
    
};

} // Yaps
