##
#
# Makefile para construir CAC6.exe
# 
# AAFR <alffore@gmail.com>
# 2015
#
#

CC= gcc -c

CLINKER= gcc -o

CFLAGS= -O3 -Wall

LIBS= -lm -lpq -lpthread

OBJ= main.o \
recuperaInfoL.o \
recuperaInfoR.o \
algoritmo.o   
	
	

 
DIR_SRC=./src/
DIR_BIN=./bin/

all: clean $(OBJ)
	$(CLINKER) $(DIR_BIN)CAC6.exe $(OBJ) $(LIBS) $(CFLAGS)


%.o: $(DIR_SRC)%.c
	$(CC) $(CFLAGS)  $<


docs: borradocs
	doxygen docs/CAC6.dox 


borradocs:

	@rm -rf docs/html
	

clean:
	@rm -rfv *.o

sc: clean
	@rm -rf *.exe
	