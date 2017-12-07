IDIR =./include
CC=g++
CFLAGS=-I$(IDIR)
DEFINES=

SDIR=./src

_DEPS = Brkga.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Brkga.o main.o 
OBJ = $(patsubst %,$(SDIR)/%,$(_OBJ))


%.o:%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEFINES)

all: main

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DEFINES)

.PHONY: clean

clean:
	rm -f $(SDIR)/*.o
