SDIR = ./src

IDIR = ./include
CC = gcc
CFLAGS = -I$(IDIR) -Wall -Werror

_DEPS = sort.h
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

BDIR = bin
BIN_genvar = $(BDIR)/genvar
BIN_dumpvar = $(BDIR)/dumpvar
BIN_varsort = $(BDIR)/arsort
OBJ_genvar = $(BIN_genvar).o
OBJ_dumpvar = $(BIN_dumpvar).o
OBJ_varsort = $(BIN_varsort).o

$(BDIR)/%.o : $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prepare : $(OBJ_genvar) $(OBJ_dumpvar)
	$(CC) -o $(BIN_genvar) $(OBJ_genvar) $(CFLAGS)
	$(CC) -o $(BIN_dumpvar) $(OBJ_dumpvar) $(CFLAGS)

varsort : $(OBJ_varsort)
	


.PHONY: clean

clean:
	@rm -f $(BDIR)/*
