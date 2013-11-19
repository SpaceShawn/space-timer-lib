CC=gcc
CXX=g++
CXX_FLAGS=-fpermissive
MICROCC=microblaze-unknown-linux-gnu-gcc
MICROPP=microblaze-unknown-linux-gnu-g++
#CFLAGS=-static
MICROCFLAGS=-c -mcpu=v8.10.a -mxl-barrel-shift -mxl-multiply-high -mxl-pattern-compare -mno-xl-soft-mul -mno-xl-soft-div -mxl-float-sqrt -mhard-float -mxl-float-convert -ffixed-r31 --sysroot /usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/sys-root 
DEBUGFLAGS=-ggdb -g -gdwarf-2 -g3 #gdwarf-2 + g3 provides macro info to gdb
MICROINCPATH=-I./inc/
INCPATH=-I./inc/
LIBPATH=-L./lib
MICROLIBPATH=-L/usr/local/lib/mbgcc/microblaze-unknown-linux-gnu/lib

buildBinCpp:
	$(CXX) $(CXX_FLAGS) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c src/timer.c -o lib/timer.o
buildBin:
	$(CC) $(INCPATH) $(LIBPATH) $(DEBUGFLAGS) -static -c src/timer.c -o lib/timer.o
buildQ6:
	$(MICROCC) $(MICROCFLAGS) $(MICROINCPATH) $(MICROLIBPATH) $(DEBUGFLAGS) -static -c src/timer.c -o lib/timer-mbcc.o

#buildAllTests: buildUnitTests
#buildUnitTests:
#	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(INCPATH) $(INCTESTPATH) $(LIBPATH) src/*.c tests/unit/*.c -o bin/AllUnitTests $(LIBS)
