/**********************************************************************
 * SimLoader: Executable File Loader for Processor Simulators         *
 *  as a part of SimMips: Simple Computer Simulator of MIPS           *
 * Copyright (C) 2008-2012 Arch Lab. Tokyo Institute of Technology    *
 *  Dual licensed under New BSD or GPL v2 licenses.                   *
 *  See COPYING file on the base directory for more information.      *
 **********************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "elf.h"

#include "../lib/Singleton.h"
#include "../lib/CreatorUsingNew.h"

namespace Yaps {

enum {
    ST_NOTYPE = 0,
    ST_FUNC   = 1,
    ST_OBJECT = 2,
    FI_LITTLE = 0,
    FI_BIG    = 1,
};

using namespace MyLibrary;

class SimLoader : public Singleton<SimLoader>
                , public CreatorUsingNew<SimLoader> {
    friend class CreatorUsingNew<SimLoader>;
    
 public:
    typedef struct {
        unsigned int  addr;
        unsigned char data;
    } memtab_t;

    typedef struct {
        unsigned int addr;
        int          type;
        char        *name;
        std::string namestr;
    } symtab_t;
    
    unsigned int entryPoint() const {return entry;}
    unsigned int stackPointer() const {return stackptr;}
    std::vector<memtab_t>& memoryTable() {return memtab;}
    int theNumberOfMemoryTable() const {return memtabnum;}
    
    int filetype;
    int endian;
    int archtype;
    int dynamic;
    unsigned int phoff, phsize, phnum, phstart;
    
    int loadfile(const char *);
    int loadfile(std::string);
    unsigned int getSymbolAddress(const char *);

 protected:
    ~SimLoader() {}
 private:
    SimLoader();
    
    
    bool checkfile(std::ifstream &);
    bool loadelf32(std::ifstream &);

    unsigned int entry;
    unsigned int stackptr;
    
    std::vector<memtab_t> memtab;
    std::vector<symtab_t> symtab;
    
    int memtabnum;
    int symtabnum;

    void printArchitecture() const;
};

} // Yaps
