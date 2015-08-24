/**
 * ISA.cc
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
#include "./ISA.h"

#include "./Decoder.h"
#include "./RegisterFile.h"
#include "./SystemCallExecutor.h"
/**********************************************************************/
namespace Yaps {

namespace MIPS {

/**
 * Default constructor
 */
ISA::ISA() {
    setFactoryMethod<Yaps::IDecoder>([](){return Decoder::instance();});
    setFactoryMethod<Yaps::RegisterFile>([](){return new RegisterFile();});
    setFactoryMethod<Yaps::SystemCallExecutor>([](){return new SystemCallExecutor();});
}

/**
 * Default destructor
 */
ISA::~ISA() {
}


} // MIPS

namespace {

bool registerISA = Yaps::ISA::add(EM_MIPS, [](){return new MIPS::ISA();});

}

} // Yaps
