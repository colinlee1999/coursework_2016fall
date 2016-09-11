CC = gcc

IDIR = ./include
SDIR = ./src
BDIR = ./bin

FLAGS1 = -Wall -Werror -I$(IDIR)
FLAGS2 = -O -Wall -I$(IDIR)

prepare : $(SDIR)/genvar.c $(SDIR)/dumpvar.c
	$(CC) -o $(BDIR)/genvar.out $(SDIR)/genvar.c $(FLAGS1)
	$(CC) -o $(BDIR)/dumpvar.out $(SDIR)/dumpvar.c $(FLAGS1)

sort : $(SDIR)/varsort.c
	$(CC) -o $(BDIR)/varsort.out $(SDIR)/varsort.c $(FLAGS2)

.PHONY : clean

clean :
	@rm -f $(BDIR)/*
