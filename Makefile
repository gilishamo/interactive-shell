CC=gcc
CFLAGS=-I.
DEPS = utils.h interactive_shell_handler.h
OBJ = utils.c interactive_shell_handler.o main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

interactive_shell:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean :
	rm -rf *.o