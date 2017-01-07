CC=gcc
CFLAGS=-I.
DEPS = disp.hpp
OBJ = disp.o tester.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tester: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)