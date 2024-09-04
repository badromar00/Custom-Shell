#Makefile for Custom Shell
#Omar Badr
###########################################################
# Executable dsh
EXEC = dsh

#source files
FILES = dsh.cpp xsh.cpp
CC = g++

#flags
LFLAGS = -g
CFLAGS = -g -std=c++11 -c

#object file
OBJECTS = $(FILES:.cpp=.o)

# Rule to build executable dsh
$(EXEC): $(OBJECTS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)
	rm -f *.o

#Rule to make sure that it compiles the source file into object files
.cpp.o:
	$(CC) $(CFLAGS) $<

#Rule to clean up files
clean:
	rm -f *.o $(EXEC)
#######################[ EOF: Makefile ]###################
