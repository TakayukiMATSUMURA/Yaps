/**
 * ISA.h
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

#include "../common/ISA.h"
#include "../common/Decoder.h"
#include "../common/RegisterFile.h"
#include "../common/SystemCallExecutor.h"

namespace Yaps {

namespace MIPS {

class ISA : public Yaps::ISA {
public:
    /// Default constructor
    ISA ();
        
    /// Destructor
    virtual ~ISA ();
    
    // opcode
    static const int SPECIAL  = 0b000000;
    static const int REGIMM   = 0b000001;
    static const int J        = 0b000010;
    static const int JAL      = 0b000011;
    static const int BEQ      = 0b000100;
    static const int BNE      = 0b000101;
    static const int BLEZ     = 0b000110;
    static const int BGTZ     = 0b000111;
    static const int ADDI     = 0b001000;
    static const int ADDIU    = 0b001001;
    static const int SLTI     = 0b001010;
    static const int SLTIU    = 0b001011;
    static const int ANDI     = 0b001100;
    static const int ORI      = 0b001101;
    static const int XORI     = 0b001110;
    static const int LUI      = 0b001111;
    
    static const int COP0     = 0b010000;
    static const int COP1     = 0b010001;
    static const int COP2     = 0b010010;
    static const int COP1X    = 0b010011;
    static const int BEQL     = 0b010100;
    static const int BNEL     = 0b010101;
    static const int BLEZL    = 0b010110;
    static const int BGTZL    = 0b010111;

    static const int SPECIAL2 = 0b011100;
    static const int JALX     = 0b011101;
    
    static const int SPECIAL3 = 0b011111;

    static const int LB       = 0b100000;
    static const int LH       = 0b100001;
    static const int LWL      = 0b100010;
    static const int LW       = 0b100011;
    static const int LBU      = 0b100100;
    static const int LHU      = 0b100101;
    static const int LWR      = 0b100110;

    static const int SB       = 0b101000;
    static const int SH       = 0b101001;
    static const int SWL      = 0b101010;
    static const int SW       = 0b101011;
    
    static const int SWR      = 0b101110;
    static const int CACHE    = 0b101111;
    
    static const int LL       = 0b110000;
    static const int LWC1     = 0b110001;
    static const int LWC2     = 0b110010;
    static const int PREF     = 0b110011;
    
    static const int LDC1     = 0b110101;
    static const int LDC2     = 0b110110;
    
    static const int SC       = 0b111000;
    static const int SWC1     = 0b111001;
    static const int SWC2     = 0b111010;
    
    static const int SDC1     = 0b111101;
    static const int SDC2     = 0b111110;

    
    // SPECIAL opcode of function
    static const int SLL       = 0b000000;
    static const int MOVCI     = 0b000001;
    static const int SRL       = 0b000010;
    static const int SRA       = 0b000011;
    static const int SLLV      = 0b000100;
    static const int SRLV      = 0b000110;
    static const int SRAV      = 0b000111;
    
    static const int JR        = 0b001000;
    static const int JALR      = 0b001001;
    static const int MOVZ      = 0b001010;
    static const int MOVN      = 0b001011;
    static const int SYSCALL   = 0b001100;
    static const int BREAK     = 0b001101;
    static const int SYNC      = 0b001111;
    
    static const int MFHI      = 0b010000;
    static const int MTHI      = 0b010001;
    static const int MFLO      = 0b010010;
    static const int MTLO      = 0b010011;

    static const int MULT      = 0b011000;
    static const int MULTU     = 0b011001;
    static const int DIV       = 0b011010;
    static const int DIVU      = 0b011011;
    
    static const int ADD       = 0b100000;
    static const int ADDU      = 0b100001;
    static const int SUB       = 0b100010;
    static const int SUBU      = 0b100011;
    static const int AND       = 0b100100;
    static const int OR        = 0b100101;
    static const int XOR       = 0b100110;
    static const int NOR       = 0b100111;

    static const int SLT       = 0b101010;
    static const int SLTU      = 0b101011;

    static const int TGE      = 0b110000;
    static const int TGEU     = 0b110001;
    static const int TLT      = 0b110010;
    static const int TLTU     = 0b110011;
    static const int TEQ      = 0b110100;
    
    static const int TNE      = 0b110110;

    
    // Regimm definition
    static const int BLTZ       = 0b00000;
    static const int BGEZ       = 0b00001;
    static const int BLTZL      = 0b00010;
    static const int BGEZL      = 0b00011;
    
    static const int TGEI       = 0b01000;
    static const int TGEIU      = 0b01001;
    static const int TLTI       = 0b01010;
    static const int TLTIU      = 0b01011;
    static const int TEQI       = 0b01100;
    
    static const int TNEI       = 0b01110;
    
    static const int BLTZAL     = 0b10000;
    static const int BGEZAL     = 0b10001;
    static const int BLTZALL    = 0b10010;
    static const int BGEZALL    = 0b10011;

    static const int SYNCI      = 0b11111;
    
    
    // SPECIAL2 opcode of function
    static const int MADD     = 0b000000;
    static const int MADDU    = 0b000001;
    static const int MUL      = 0b000010;
    
    static const int MSUB     = 0b000100;
    static const int MSUBU    = 0b000101;

    static const int CLZ      = 0b100000;
    static const int CLO      = 0b100001;
    
    static const int SDBBP    = 0b111111;

    
    // SPECIAL3 opcode of function
    static const int EXT      = 0b000000;
    
    static const int INS      = 0b000100;

    static const int BSHFL    = 0b100000;

    static const int RDHWR    = 0b111011;
    
    // BSHFL sa
    static const int WSBH     = 0b00010;
    
    static const int SEB      = 0b10000;
    
    static const int SEH      = 0b11000;
};

} // MIPS

} // Yaps
