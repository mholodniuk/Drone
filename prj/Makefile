INC=inc
CC=g++
CFLAGS=-Wall -pedantic -g

SRC=src
DAT=dat
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main
LIBS=-lm

__start__: $(OBJ) $(DAT) ./$(BIN)
	rm -f core.* core; ./$(BIN)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

$(TEST)/bin:
	mkdir $@

$(OBJ):
	mkdir $@

$(DAT):
	mkdir $@

clean:
	rm -f $(OBJ)/*.o $(BINDIR)/*

debug:
	gdb bin/main