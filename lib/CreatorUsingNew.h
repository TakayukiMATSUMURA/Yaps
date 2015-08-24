/**
 * CreatorUsingNew.h
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

template <class T>
class CreatorUsingNew {
public:
    template <class... Args>
    static T* create(Args... args) {
        return new T(args...);
    }
    
    static void destroy(T* instance) {
        delete instance;
    }
    
protected:
    /// Destructor
    ~CreatorUsingNew() {}
};

} // MyLibrary
