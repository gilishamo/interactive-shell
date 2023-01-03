CC=gcc
CFLAGS=-I.
LIBS=-lpsapi 
DEPS = utils.h interactive_shell_handler.h
OBJ = utils.c interactive_shell_handler.o main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

interactive_shell:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean :
	rm -rf *.o