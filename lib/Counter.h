/**
 * Counter.h
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

#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>

namespace MyLibrary {

template<class IndexType = int>
class Counter {
public:
    void count(IndexType index) {
        auto i = histogram_.find(index);
        if(i == histogram_.end()) histogram_[index] = 0;
        
        histogram_[index]++;
    }
    
    double getRateOf(IndexType index) const {
        unsigned long long int sum = 0;
        for(auto it = histogram_.begin(); it != histogram_.end(); it++)
            sum += it->second;
        
        return (double)histogram_.find(index)->second / (double)sum;
    }
    
    void reset() {
        histogram_.clear();
    }
    
    unsigned long long int operator[](IndexType index) const {
        return histogram_[index];
    }
    
    void saveDataTo(std::string fileName) const {
        std::ofstream ofs(fileName);
        for(auto it = histogram_.begin(); it != histogram_.end(); it++) {
            ofs << it->first << "," << it->second << std::endl;
        }
    }
    
    std::string toString() const {
        std::stringstream ss;
        
        int i = 0;
        for(auto it = histogram_.begin(); it != histogram_.end(); it++) {
            ss << it->first << ": " << it->second;
            i++;
            if(i < size()) ss << std::string("\n");
        }
        
        return ss.str();
    }
    
    std::string toStringInDescendingOrder() const {
        std::stringstream ss;
        auto sortedHistogram = getMapExchanedKeysAndValues();
        
        unsigned long long int prevEntryCounter = 0;
        int ranking = 0;
        for(auto it = sortedHistogram.rbegin(); it != sortedHistogram.rend(); it++) {
            ss << getRankingString(it->first, prevEntryCounter, ranking);
            
            ss << " ";
            ss << std::left << std::setw(10) << it->second;
            ss << std::right << std::setw(10) << it->first;
            ss << getPercentStringOf(it->second);
            
            prevEntryCounter = it->first;
        }
        ss << getResultString();
        
        return ss.str();
    }
    
    int size() const {return histogram_.size();}
    
private:
    std::map<IndexType, unsigned long long int> histogram_;

    int getDigitOfEntries() const {return log10(this->size()) + 1;}
    
    std::multimap<unsigned long long int, IndexType> getMapExchanedKeysAndValues() const {
        std::multimap<unsigned long long int, IndexType> result;
        
        for(auto it = histogram_.begin(); it != histogram_.end(); it++) {
            std::pair<unsigned long long int, IndexType> pair;
            pair.first = it->second;
            pair.second = it->first;
            
            result.insert(pair);
        }
        
        return result;
    }
    
    std::string getRankingString(unsigned long long count,
                                 unsigned long long prevEntryCounter,
                                 int& ranking) const {
        std::stringstream ss;
        
        const int digit = getDigitOfEntries();
        if(count != prevEntryCounter) {
            ranking++;
            ss << "[" << std::right << std::setw(digit) << ranking << "]";
            return ss.str();
        }
        
        for(int i = 0; i < digit + 2; i++) ss << " ";
        return ss.str();
    }
    
    std::string getResultString() const {
        std::stringstream ss;
        ss << "[";
        for(int i = 0; i < getDigitOfEntries(); i++) ss << "-";
        ss << "] ";
        ss << std::left << std::setw(10);
        ss << "total";
        
        unsigned long long sum = 0;
        double totalPercentage = 0;
        for(auto it = histogram_.begin(); it != histogram_.end(); it++) {
            sum += it->second;
            totalPercentage += getRateOf(it->first) * 100;
        }
        
        ss << std::right << std::setw(10) << sum;
        ss << " (" << std::setw(6) << std::right << std::fixed;
        ss << std::setprecision(3) << totalPercentage << "%)";
        
        return ss.str();
    }
    
    std::string getPercentStringOf(IndexType target) const {
        std::stringstream ss;
        ss << " (" << std::setw(7) << std::right << std::fixed;
        const auto percent = getRateOf(target) * 100;
        ss << std::setprecision(3) << percent << "%)" << std::endl;
        
        return ss.str();
    }
};

} // MyLibrary
