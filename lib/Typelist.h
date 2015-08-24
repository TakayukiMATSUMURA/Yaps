/**
 * Typelist.h
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

namespace MyLibrary {

class NullType {};
class EmptyType {};


template <class T, class U> struct Typelist;

template <class T, class U>
struct Typelist {
    using First = T;
    using Else = U;
};


template <class... T> struct MakeTypelist {};

template <>
struct MakeTypelist<> {
    using Result = NullType;
};

template <class T>
struct MakeTypelist<T, NullType> {
    using Result = Typelist<T, NullType>;
};

template <class T, class... U>
struct MakeTypelist<T, U...> {
    using Result = Typelist<T, typename MakeTypelist<U...>::Result>;
};


template <class TList> struct Length;

template <>
struct Length<NullType> {
    static const int value = 0;
};

template <class First, class Else>
struct Length<Typelist<First, Else>> {
    static const int value = Length<Else>::value + 1;
};


template <class TList, unsigned int index> struct TypeAt;

template <>
struct TypeAt<NullType, 0> {
    using Result = NullType;
};

template <class First, class Else>
struct TypeAt<Typelist<First, Else>, 0> {
    using Result = First;
};

template <class First, class Else, unsigned int i>
struct TypeAt<Typelist<First, Else>, i> {
    using Result = typename TypeAt<Else, i - 1>::Result;
};

template <class TList, class T> struct IndexOf;

template <class T>
struct IndexOf<NullType, T> {
    static const int value = -1;
};

template <class T, class U>
struct IndexOf<Typelist<T, U>, T> {
    static const int value = 0;
};

template <class TList, class T>
struct IndexOf {
private:
    static const int temp = IndexOf<typename TList::Else, T>::value;
public:
    static const int value = (temp == -1) ? -1 : temp + 1;
};


template <class TList, class T> struct Erase;

template <class T>
struct Erase<NullType, T> {
    using Result = NullType;
};

template <class T, class Else>
struct Erase<Typelist<T, Else>, T> {
   using Result = Else;
};

template <class First, class Else, class T>
struct Erase<Typelist<First, Else>, T> {
    using Result = Typelist<First, typename Erase<Else, T>::Result>;
};


template <class TList, class T> struct Add;

template <>
struct Add<NullType, NullType> {
    using Result = NullType;
};

template <class T>
struct Add<NullType, T> {
    using Result = typename MakeTypelist<T>::Result;
};

template <class First, class Else>
struct Add<NullType, Typelist<First, Else>> {
    using Result = Typelist<First, Else>;
};

template <class First, class Else, class T>
struct Add<Typelist<First, Else>, T> {
    using Result = Typelist<First, typename Add<Else, T>::Result>;
};

} // MyLibrary
