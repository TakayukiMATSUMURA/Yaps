all:
	g++ -std=c++11 -O3 -o Yaps main.cc loader/simloader.cc MIPS/ISA.cc MIPS/RegisterFile.cc
	./Yaps
run:
	./Yaps -i sample/hello.elf
clean:
	rm Yaps
