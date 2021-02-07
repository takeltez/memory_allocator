my_malloc := bin/my_malloc
CC := gcc
CFLAGS := -Wall

all: $(my_malloc)

$(my_malloc): build/main.o build/my_malloc.o build/chunk_handler.o build/logger.o build/my_free.o
		$(CC) $(CFLAGS) build/main.o build/my_malloc.o build/chunk_handler.o build/logger.o build/my_free.o -o $(my_malloc)

build/main.o: src/main.c src/logger.h
		$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/my_malloc.o: src/my_malloc.c src/my_malloc.h src/chunk_handler.h
		$(CC) $(CFLAGS) -c src/my_malloc.c -o build/my_malloc.o

build/my_free.o: src/my_free.c src/my_free.h src/my_malloc.h
		$(CC) $(CFLAGS) -c src/my_free.c -o build/my_free.o

build/chunk_handler.o: src/chunk_handler.c src/chunk_handler.h src/my_malloc.h
		$(CC) $(CFLAGS) -c src/chunk_handler.c -o build/chunk_handler.o

build/logger.o: src/logger.c src/logger.h src/my_free.h src/my_malloc.h
		$(CC) $(CFLAGS) -c src/logger.c -o build/logger.o

dir:
	@mkdir build
	@mkdir bin
		
clean:
	@rm bin/*
	@rm build/*.o