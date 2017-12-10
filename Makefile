IDIR =./include
CC=g++-7
CFLAGS=-I$(IDIR) 
DEFINES=
INSTANCE=dummy

SDIR=./src

_DEPS = Brkga.h DummyModel.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Brkga.o DummyModel.o
OBJ = $(patsubst %,$(SDIR)/%,$(_OBJ))


%.o:%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEFINES)

all: main

parallel: CFLAGS += -fopenmp
parallel: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DEFINES)

dummy: INSTANCE = dummy
dummy: main

main: $(OBJ) src/$(INSTANCE).o
	$(CC) -o $(INSTANCE) $^ $(CFLAGS) $(DEFINES)

.PHONY: clean

clean:
	rm -f $(SDIR)/*.o
