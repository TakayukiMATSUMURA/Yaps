/**
 * AbstractFactory.h
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

#include <vector>

#include "./Factory.h"
#include "./CreatorUsingLambda.h"
#include "./BinaryTreeInheritance.h"

namespace MyLibrary {

template<class KeyOfConcreteFactory, class... AbstractProducts>
class AbstractFactory : public BinaryTreeInheritance<CreatorUsingLambda,
                                                   AbstractProducts...> {
private:
    using FactoryType =
        AbstractFactory<KeyOfConcreteFactory, AbstractProducts...>;
    using CreatorType =
        std::function<AbstractFactory<KeyOfConcreteFactory,
                                      AbstractProducts...>*()>;
    
public:
    virtual ~AbstractFactory() {
        delete factoryFactory_;
    }
    
    template<class T>
    T* create() const {
        const CreatorUsingLambda<T>& unit = *this;
        return unit.create();
    }
    
    static bool add(const KeyOfConcreteFactory& key, CreatorType lambda) {
        factoryFactory_->add(key, lambda);
        return true;
    }
    
    static FactoryType* getFactoryFrom(const KeyOfConcreteFactory& key) {
        return factoryFactory_->createFrom(key);
    }
    
    static bool unregister(const KeyOfConcreteFactory& id) {
        return factoryFactory_->unregister(id);
    }
    
protected:
    template<class T, class U>
    void setFactoryMethod(U creator) {
        CreatorUsingLambda<T>& unit = *this;
        unit.set(creator);
    }

private:
    static Factory<FactoryType, KeyOfConcreteFactory>* factoryFactory_;
};

template <class KeyOfConcreteFactory, class... AbstractProducts>
Factory<AbstractFactory<KeyOfConcreteFactory, AbstractProducts...>, KeyOfConcreteFactory>*
AbstractFactory<KeyOfConcreteFactory, AbstractProducts...>::factoryFactory_ =
new Factory<FactoryType, KeyOfConcreteFactory>();

} // MyLibrary
/**********************************************************************/
