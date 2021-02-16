my_malloc := bin/my_malloc
CC := gcc
CFLAGS := -Wall

all: $(my_malloc)

$(my_malloc): build/main.o build/my_malloc.o build/chunk_handler.o build/logger.o build/my_free.o build/rbtree.o
		$(CC) $(CFLAGS) build/main.o build/my_malloc.o build/chunk_handler.o build/logger.o build/my_free.o build/rbtree.o -o $(my_malloc)

build/main.o: src/main.c src/logger/logger.h
		$(CC) $(CFLAGS) -c src/main.c -o build/main.o -Isrc/logger -Isrc/rbtree  -Isrc/alloc

build/my_malloc.o: src/alloc/my_malloc.c src/alloc/my_malloc.h src/alloc/chunk_handler.h src/rbtree/rbtree.h
		$(CC) $(CFLAGS) -c src/alloc/my_malloc.c -o build/my_malloc.o -Isrc/rbtree -Isrc/alloc

build/my_free.o: src/alloc/my_free.c src/alloc/my_free.h src/alloc/my_malloc.h src/rbtree/rbtree.h
		$(CC) $(CFLAGS) -c src/alloc/my_free.c -o build/my_free.o -Isrc/rbtree -Isrc/alloc

build/chunk_handler.o: src/alloc/chunk_handler.c src/alloc/chunk_handler.h src/alloc/my_malloc.h src/rbtree/rbtree.h
		$(CC) $(CFLAGS) -c src/alloc/chunk_handler.c -o build/chunk_handler.o -Isrc/rbtree -Isrc/alloc

build/logger.o: src/logger/logger.c src/logger/logger.h src/alloc/my_free.h src/alloc/my_malloc.h
		$(CC) $(CFLAGS) -c src/logger/logger.c -o build/logger.o -Isrc/alloc -Isrc/rbtree

build/rbtree.o: src/rbtree/rbtree.c src/rbtree/rbtree.h src/alloc/my_malloc.h
		$(CC) $(CFLAGS) -c src/rbtree/rbtree.c -o build/rbtree.o -Isrc/alloc 

dir:
	@mkdir build
	@mkdir bin
		
clean:
	@rm bin/*
	@rm build/*.o