time_measuring := bin/time_measuring
CC := gcc
CFLAGS := -Wall

all: $(time_measuring)

$(time_measuring): build/time_measuring.o 
		$(CC) $(CFLAGS) build/time_measuring.o -ldl -o $(time_measuring)


build/time_measuring.o: src/time_measuring.c
		$(CC) $(CFLAGS) -c src/time_measuring.c -o build/time_measuring.o

dir:
	@mkdir bin
	@mkdir build
		
clean:
	@rm bin/*
	@rm build/*