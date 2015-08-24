/**
 * BinaryData.h
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

#include <string>
#include <sstream>
#include <iomanip>

using uint = unsigned int;
using ulong = unsigned long int;

namespace Yaps {

class BinaryData {
public:
    /// Default constructor
    BinaryData (uint width = 32, ulong value = 0) :
        value_(value & mask(width)), width_(width) {}
    
    /// Destructor
    virtual ~BinaryData () {}
    
    BinaryData& operator= (const BinaryData& obj) {
        this->width_ = obj.width();
        this->value_ = obj.value() & BinaryData::mask(width());
        return *this;
    }
    
    BinaryData& operator= (const ulong& value) {
        this->value_ = value & mask(width());
        return *this;
    }
    
    int bit (uint index) const {
        return (value() & (1 << index)) ? 1 : 0;
    }
    BinaryData byte (uint index) const {
        ulong byteMask = mask(8) << (index * 8);
        return BinaryData(8, (value() & byteMask) >> (index * 8));
    }
    
    BinaryData zeroExtension (uint width) const {
        return BinaryData(width, value());
    }
    BinaryData signExtension (uint width) const {
        if(width <= this->width()) return BinaryData(width, this->value());
        
        ulong resultValue = this->value();
        ulong signBit = bit(this->width() - 1);
        for(uint i = this->width(); i < width; i++)
            resultValue |= signBit << i;
        
        return BinaryData(width, resultValue);
    }
    
    BinaryData shiftRightArithmetic (uint shamt) const {
        ulong resultValue = this->value();
        ulong sign = bit(this->width() - 1) << (this->width() - 1);
        for(uint i = 0; i < shamt; i++) {
            resultValue = (resultValue >> 1) | sign;
        }
        return BinaryData(this->width(), resultValue);
    }
    
    virtual std::string toString () const {
        std::string tmp = "";
        for (int i = this->width() - 1; i >= 0; i--)
            tmp += (bit(i) == 0) ? "0" : "1";
        
        return tmp;
    }
    virtual std::string toStringInHexadecimal (bool leadingZero = true) const {
        std::stringstream ss;
        ss.setf(std::ios::hex, std::ios::basefield);
        if(leadingZero)
            ss << std::setw(this->width() / 4) << std::setfill('0');
        
        ss << value();
        return ss.str();
    }
    virtual std::string toStringSignedDecimal () const {
        long int value = getValueAs<long int>();
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    static ulong mask (uint num) {
        if(num == 0) return 0;
        
        ulong mask = 0;
        for (uint i = 0; i < num; i++)
            mask |= static_cast<ulong>(1) << i;
        
        return mask;
    }

    operator ulong() const {
        return value_ & mask (this->width());
    }

    long int signedValue () const {
        return getValueAs<long int>();
    }
    
    template <typename T>
    T getValueAs() const {
        ulong data = signExtension(64);
        union {
            ulong u;
            T t;
        };
        u = data;
        return t;
    }
    
    template <typename T>
    void setValueAs(T arg) {
        union {
            ulong u;
            T t;
        };
        t = arg;
        this->set(u);
    }
    
    ulong value () const {return value_ & mask(this->width());}
    virtual void set (ulong v) {value_ = v & mask(this->width());}
    uint width () const {return width_;}
    
private:
    uint width_;
    ulong value_;
};

} // Yaps
