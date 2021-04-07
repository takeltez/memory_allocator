prog := bin/prog
CC := gcc
CFLAGS := -Wall

all: $(prog)

$(prog): build/prog.o 
		$(CC) $(CFLAGS) build/prog.o -ldl -o $(prog)


build/prog.o: src/prog.c
		$(CC) $(CFLAGS) -c src/prog.c -o build/prog.o

dir:
	@mkdir bin
	@mkdir build
		
clean:
	@rm bin/*
	@rm build/*