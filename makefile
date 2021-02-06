my_malloc := bin/my_malloc
CC := gcc
CFLAGS := -Wall

all: $(my_malloc)

$(my_malloc): build/main.o build/my_malloc.o
		$(CC) $(CFLAGS) build/main.o build/my_malloc.o -o $(my_malloc)

build/main.o: src/main.c
		$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/my_malloc.o: src/my_malloc.c src/my_malloc.h
		$(CC) $(CFLAGS) -c src/my_malloc.c -o build/my_malloc.o

dir:
	@mkdir build
	@mkdir bin
		
clean:
	@rm bin/*
	@rm build/*.o