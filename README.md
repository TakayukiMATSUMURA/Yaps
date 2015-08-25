# Yaps: Yet another processor simulator
A processor simulator, which is designed for readability and scalability rather than execution speed.  
It is aimed at simulating various ISAs and Microarchitectures.

## Install
    $ git clone git://github.com/TakayukiMATSUMURA/yaps  
    Cloning into 'yaps'...  
    remote: Counting objects: 160, done.  
    remote: Compressing objects: 100% (53/53), done.  
    remote: Total 160 (delta 105), reused 155 (delta 104), pack-reused 0  
    Receiving objects: 100% (160/160), 243.08 KiB | 249.00 KiB/s, done.  
    Resolving deltas: 100% (105/105), done.  
    Checking connectivity... done.  
    $ cd yaps  
    $ make  
    g++ -std=c++11 -O3 -o Yaps main.cc loader/simloader.cc MIPS/ISA.cc MIPS/RegisterFile.cc  
    ./Yaps  
    Yaps: Yet Another Processor Simulator  
    usage: Yaps [options] binaryFileName  
    options  
     -e [num][kmg]: stop simulation after num cycles executed  
     -d 1: put the architectural state after simulation  
        2: put all the instructions executed  
     -i: put the instruction mix after simulation

        
## Hello World
    $ make run
    ./Yaps -i sample/hello.elf
    Yaps: Yet Another Processor Simulator
    i mix mode.
    Hello World
    system call stop
    ##### Simulation Results #####
    inst count: 2834
    cycle count: 2876
    IPC: 0.985396
    MIPS: 0.65526
    [ 1] addiu           1011 ( 35.153%)
    [ 2] bnel             346 ( 12.031%)
    [ 3] sb               319 ( 11.092%)
    [ 4] lw               280 (  9.736%)
    [ 5] lbu              191 (  6.641%)
    [ 6] addu             170 (  5.911%)
    [ 7] sw               158 (  5.494%)
    [ 8] beq               58 (  2.017%)
    [ 9] jalr              50 (  1.739%)
    [10] jr                49 (  1.704%)
    [11] bne               48 (  1.669%)
    [12] lui               45 (  1.565%)
    [13] nop               42 (  1.460%)
    [14] andi              14 (  0.487%)
    [15] subu              13 (  0.452%)
    [16] lhu               12 (  0.417%)
         lb                12 (  0.417%)
    [17] beql               8 (  0.278%)
    [18] sll                6 (  0.209%)
    [19] sltu               5 (  0.174%)
    [20] syscall            4 (  0.139%)
         sra                4 (  0.139%)
         bgezal             4 (  0.139%)
    [21] xor                3 (  0.104%)
         sltiu              3 (  0.104%)
         sh                 3 (  0.104%)
         movz               3 (  0.104%)
    [22] teq                2 (  0.070%)
         slti               2 (  0.070%)
         ori                2 (  0.070%)
         mflo               2 (  0.070%)
         divu               2 (  0.070%)
    [23] nor                1 (  0.035%)
         mul                1 (  0.035%)
         movn               1 (  0.035%)
         bltz               1 (  0.035%)
         and                1 (  0.035%)
    [--] total           2876 (100.000%)
 
 
## Annotation
The Followings are modified and redistributed.

[/loader/elf.h](https://github.com/TakayukiMATSUMURA/Yaps/blob/master/loader/elf.h)  
from [glibc](https://sourceware.org/git/?p=glibc.git;a=summary)  

[/loader/simloader.h](https://github.com/TakayukiMATSUMURA/Yaps/blob/master/loader/simloader.h)  
[/loader/simloader.cc](https://github.com/TakayukiMATSUMURA/Yaps/blob/master/loader/simloader.cc)  
[/MIPS/SystemCallExecutor.h](https://github.com/TakayukiMATSUMURA/Yaps/blob/master/MIPS/SystemCallExecutor.h)  
from [SimMips](http://www.arch.cs.titech.ac.jp/SimMips/)