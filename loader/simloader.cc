/**********************************************************************
 * SimLoader: Executable File Loader for Processor Simulators         *
 *  as a part of SimMips: Simple Computer Simulator of MIPS           *
 * Copyright (C) 2008-2012 Arch Lab. Tokyo Institute of Technology    *
 *  Dual licensed under New BSD or GPL v2 licenses.                   *
 *  See COPYING file on the base directory for more information.      *
 **********************************************************************/
#include "simloader.h"

#include "../common/SystemConfigure.h"
/**********************************************************************/
namespace Yaps {

SimLoader::SimLoader()
{
    filetype = endian = archtype = dynamic = 0;
    memtabnum = symtabnum = 0;
    entry = stackptr = 0;
    phoff = phsize = phnum = phstart = 0;

    loadfile(SystemConfigure::instance()->binaryFileName());
}

/**********************************************************************/
bool SimLoader::checkfile(std::ifstream &ifs)
{
    unsigned char e_ident[EI_NIDENT];
    ifs.seekg(0, std::ios_base::beg);
    ifs.read((char *)e_ident, EI_NIDENT);

    /* check magic */
    if (e_ident[EI_MAG0] != ELFMAG0 || e_ident[EI_MAG1] != ELFMAG1 ||
        e_ident[EI_MAG2] != ELFMAG2 || e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "## ERROR: file is not ELF format.");
        return false;
    }
    
    /* check class */
    if (e_ident[EI_CLASS] != ELFCLASS32) {
        fprintf(stderr, "## ERROR: non-32bit ELF is not supported.");
        return false;
    }
    
    /* check endian */
    if (e_ident[EI_DATA] == ELFDATA2LSB) {
        endian = FI_LITTLE;
    } else if (e_ident[EI_DATA] == ELFDATA2MSB) {
        endian = FI_BIG;
    } else {
        fprintf(stderr, "## ERROR: file has unknown endianness.");
        return false;
    }

    return true;
}

/**********************************************************************/
bool SimLoader::loadelf32(std::ifstream &ifs)
{
    Elf32_Ehdr ehdr;
    Elf32_Shdr shdr, elf_strtab, elf_symtab;
    Elf32_Phdr phdr;
    Elf32_Sym  symp;
    const std::ios_base::seekdir BEG = std::ios_base::beg;
    
    /* read ELF Header */
    ifs.seekg(0, BEG);
    ifs.read((char *) &ehdr, sizeof(Elf32_Ehdr));
    filetype = ehdr.e_type;
    archtype = ehdr.e_machine;
    
    entry    = ehdr.e_entry;
    phoff    = ehdr.e_phoff;
    phsize   = ehdr.e_phentsize;
    phnum    = ehdr.e_phnum;

    /* read Program Header (for loading program) */
    bool phstart_set = false;
    ifs.seekg(phoff, BEG);
    for (unsigned int i = 0; i < phnum; i++) {
        unsigned int ph_ptr = phoff + phsize * i;
        ifs.seekg(ph_ptr, BEG);
        ifs.read((char *) &phdr, sizeof(Elf32_Phdr));
        if (phdr.p_type == PT_LOAD) {
            memtab_t newmem;
            newmem.addr = phdr.p_paddr;
            ifs.seekg(phdr.p_offset, BEG);
            for (unsigned int j = 0; j < phdr.p_memsz; j++) {
                if (j < phdr.p_filesz)
                    ifs.get((char &) newmem.data);
                else
                    newmem.data = 0;
                memtab.push_back(newmem);
                newmem.addr++;
            }
            if (! phstart_set) {
                phstart_set = true;
                phstart = phoff + phdr.p_paddr - phdr.p_offset;
            }
        }
    }
    memtabnum = memtab.size();
    
    /* read Section Header (for getting additional info) */
    unsigned int sh_ptr = ehdr.e_shoff + ehdr.e_shentsize * ehdr.e_shstrndx;
    ifs.seekg(sh_ptr, BEG);
    ifs.read((char *) &shdr, sizeof(Elf32_Shdr));
    unsigned int shstr_off = shdr.sh_offset;

    elf_strtab.sh_offset  = elf_symtab.sh_offset  = 0;
    elf_strtab.sh_size    = elf_symtab.sh_size    = 0;
    elf_strtab.sh_entsize = elf_symtab.sh_entsize = 0;
    
    for (unsigned int i = 0; i < ehdr.e_shnum; i++) {
        sh_ptr = ehdr.e_shoff + ehdr.e_shentsize * i;
        ifs.seekg(sh_ptr, BEG);
        ifs.read((char *) &shdr, sizeof(Elf32_Shdr));
        std::string sname;
        ifs.seekg(shstr_off + shdr.sh_name, BEG);
        std::getline(ifs, sname, '\0');
        
        if (sname == ".strtab")
            elf_strtab = shdr;
        if (sname == ".stack")
            stackptr = shdr.sh_addr;
        if (shdr.sh_type == SHT_SYMTAB)
            elf_symtab = shdr;
        if (shdr.sh_type == SHT_DYNAMIC)
            dynamic = 1;
    }
    
    /* read Symbol table (for getting names of functions) */
    if (elf_symtab.sh_size == 0)
        return true;

    for (unsigned int i = 0;
         i < elf_symtab.sh_size / elf_symtab.sh_entsize; i++) {
        ifs.seekg(elf_symtab.sh_offset + elf_symtab.sh_entsize * i, BEG);
        ifs.read((char *) &symp, sizeof(Elf32_Sym));
        if (!symp.st_name)
            continue;
        
        symtab_t newsym;
        newsym.addr = symp.st_value;
        if      (ELF32_ST_TYPE(symp.st_info) == STT_FUNC)
            newsym.type = ST_FUNC;
        else if (ELF32_ST_TYPE(symp.st_info) == STT_OBJECT)
            newsym.type = ST_OBJECT;
        else
            newsym.type = ST_NOTYPE;
        if (elf_strtab.sh_size != 0) {
            ifs.seekg(elf_strtab.sh_offset + symp.st_name, BEG);
            std::getline(ifs, newsym.namestr, '\0');
            newsym.name = const_cast<char *>(newsym.namestr.c_str());
        }
        symtab.push_back(newsym);
    }  
    symtabnum = symtab.size();

    return true;
}

/**********************************************************************/
int SimLoader::loadfile(std::string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
    /*
    if (ifs.fail()) {
        fprintf(stderr, "## ERROR: Can't open file. (%s)\n", filename);
        return(1);
    }
    */
    if (! checkfile(ifs))
        return(1);
    
    if (endian == FI_LITTLE) {
        if (! loadelf32(ifs))
            return(1);
    } else {
        fprintf(stderr, "## ERROR: big endian is not supported.\n");
        return(1);
    }
    ifs.close();
    
    return(0);
}
/**********************************************************************/
int SimLoader::loadfile(const char *filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);

    if (ifs.fail()) {
        fprintf(stderr, "## ERROR: Can't open file. (%s)\n", filename);
        return(1);
    }
    if (! checkfile(ifs))
        return(1);

    if (endian == FI_LITTLE) {
        if (! loadelf32(ifs))
            return(1);
    } else {
        fprintf(stderr, "## ERROR: big endian is not supported.\n");
        return(1);
    }
    ifs.close();
    return(0);
}

/**********************************************************************/
unsigned int SimLoader::getSymbolAddress(const char *name)
{
    for (int i = 0; i < symtabnum; i++)
        if (symtab[i].namestr == name)
            return symtab[i].addr;
    return 0;
}

/**********************************************************************/
void SimLoader::printArchitecture () const {
    std::string arch = (archtype == EM_MIPS) ? "MIPS" : "";
        
    std::cout << "architecture: " << arch << std::endl;
    std::cout << "archtype " << archtype << std::endl;
}

} // Yaps

/*********************************************************************/
