/**
 * Wrapper.h
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

#include <sstream>

namespace MyLibrary {

template <class T>
class Wrapper {
public:
    /// Destructor
    virtual ~Wrapper() {};
    
    Wrapper(T v = 0) {
        value_ = v;
    }
    Wrapper(std::string v) {
        std::stringstream ss(v);
        ss >> value_;
    }

    Wrapper<T>& operator=(const T& value) {
        this->value_ = value;
        return *this;
    }
    
    Wrapper<T> operator++() {
        this->value_ += 1;
        return (*this);
    }
    Wrapper<T> operator++(int) {
        auto tmp = this->value_;
        this->value_ += 1;
        return tmp;
    }
    
    Wrapper<T> operator--() {
        this->value_ -= 1;
        return (*this);
    }
    Wrapper<T> operator--(int) {
        auto tmp = this->value_;
        this->value_ -= 1;
        return tmp;
    }
    
    Wrapper<T> operator+=(Wrapper<T> rhs) {
        this->value_ += rhs.value();
        return *this;
    }
    Wrapper<T> operator-=(Wrapper<T> rhs) {
        this->value_ -= rhs.value();
        return *this;
    }
    Wrapper<T> operator*=(Wrapper<T> rhs) {
        this->value_ *= rhs.value();
        return *this;
    }
    Wrapper<T> operator/=(Wrapper<T> rhs) {
        this->value_ /= rhs.value();
        return *this;
    }
    
    virtual std::string toString() const {
        std::stringstream ss;
        ss << value_;
        return ss.str();
    }
    
    operator T() const {
        return value_;
    }
    
    operator std::string() const {
        return toString();
    }

    T value() const {return value_;}
    
private:
    T value_;
};

using Char = Wrapper<char>;
using UChar = Wrapper<unsigned char>;
using Short = Wrapper<short>;
using UShort = Wrapper<unsigned short>;
using Int = Wrapper<int>;
using UInt = Wrapper<unsigned int>;
using Long = Wrapper<long>;
using ULong = Wrapper<unsigned long>;
using LongLong = Wrapper<long long>;
using ULongLong = Wrapper<unsigned long long>;
using Float = Wrapper<float>;
using Double = Wrapper<double>;
using LongDouble = Wrapper<long double>;

} // MyLibrary
