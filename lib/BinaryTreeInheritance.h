/**
 * BinaryTreeInheritance.h
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

#include "./Typelist.h"

namespace MyLibrary {

namespace Private {

template<class TList, template<class> class Unit>
class BinaryTreeInheritance;

template<class T1, class T2, template<class> class Unit>
class BinaryTreeInheritance<Typelist<T1, T2>, Unit>
    : public BinaryTreeInheritance<T1, Unit>
    , public BinaryTreeInheritance<T2, Unit> {
public:
    using LeftBase = BinaryTreeInheritance<T1, Unit>;
    using RightBase = BinaryTreeInheritance<T2, Unit>;
};

template<class AtomicType, template<class> class Unit>
class BinaryTreeInheritance : public Unit<AtomicType> {
public:
    using LeftBase = Unit<AtomicType>;
};

template<template<class> class Unit>
class BinaryTreeInheritance<NullType, Unit>{};

} // Private

template<template<class> class Unit, class... Arg>
class BinaryTreeInheritance : public Private::BinaryTreeInheritance<typename MakeTypelist<Arg...>::Result, Unit>{};

} // MyLibrary
