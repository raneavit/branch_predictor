CC = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)

# List all your .cc/.cpp files here (source files, excluding header files)
SIM_SRC = sim_bp.cc
SIM_SRC += smithCounter.cc
SIM_SRC += bimodal.cc
SIM_SRC += gshare.cc
SIM_SRC += hybrid.cc

# List corresponding compiled object files here (.o files)
SIM_OBJ = sim_bp.o
SIM_OBJ += smithCounter.o
SIM_OBJ += bimodal.o
SIM_OBJ += gshare.o
SIM_OBJ += hybrid.o
 
#################################

# default rule

all: sim
	@echo "my work is done here..."


# rule for making sim

sim: $(SIM_OBJ)
	$(CC) -o sim $(CFLAGS) $(SIM_OBJ) -lm
	@echo "-----------DONE WITH sim-----------"


# generic rule for converting any .cpp file to any .o file
 
.cc.o:
	$(CC) $(CFLAGS)  -c $*.cc

.cpp.o:
	$(CC) $(CFLAGS)  -c $*.cpp


# type "make clean" to remove all .o files plus the sim binary

clean:
	rm -f *.o sim


# type "make clobber" to remove all .o files (leaves sim binary)

clobber:
	rm -f *.o


