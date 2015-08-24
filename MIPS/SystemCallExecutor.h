/**********************************************************************
 * SimMips: Simple Computer Simulator of MIPS                         *
 * Copyright (C) 2008-2010 Arch Lab. Tokyo Institute of Technology    *
 *  Dual licensed under New BSD or GPL v2 licenses.                   *
 *  See COPYING file on the base directory for more information.      *
 **********************************************************************/
#pragma once
/**********************************************************************/
#include <unistd.h>

#include "../Memory/IMemory.h"
#include "../common/RegisterFile.h"
#include "../common/SystemCallExecutor.h"
/**********************************************************************/
namespace Yaps {

namespace MIPS {

class SystemCallExecutor : public Yaps::SystemCallExecutor {
public:
    /// Default constructor
    SystemCallExecutor() {};
    /// Destructor
    virtual ~SystemCallExecutor() {};
    
    bool execute (Yaps::RegisterFile* regFile, IMemory* memory) override {
        switch ((*regFile)[2]) {
        case EXIT:
            std::cout << "system call stop" << std::endl;
            return true;
            break;
        case WRITE:
            if ((*regFile)[4] == STDOUT_FILENO) {
                signed char c = 0;
                for (uint i = 0; i < (*regFile)[6]; i++) {
                    c = memory->read(1, (*regFile)[5] + i);
                    printf("%c", c);
                }
            }
            
            (*regFile)[2] = (*regFile)[6];
            (*regFile)[7] = 0;
            break;
        case IOCTL:
            (*regFile)[2] = (*regFile)[7] = 0;
            break;
        default:
            break;
        }
        
        return false;
    }

private:
    enum {
        EXIT = 4001,
        WRITE = 4004,
        IOCTL = 4054,
    };
};

} // MIPS

} // Yaps
