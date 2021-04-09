cmalloc := bin/cmalloc
dlib := dlib/libmalloc.so
CC := gcc
CFLAGS := -Wall

all: $(cmalloc) $(dlib)

$(cmalloc): build/main.o build/cmalloc.o build/cfree.o build/chunk_handler.o build/logger.o build/rbtree.o
		$(CC) $(CFLAGS) build/main.o build/cmalloc.o build/cfree.o build/chunk_handler.o build/logger.o build/rbtree.o -o $(cmalloc)

$(dlib): build/cmalloc.o build/cfree.o build/chunk_handler.o build/logger.o build/rbtree.o
		$(CC) $(CFLAGS) -shared build/cmalloc.o build/cfree.o build/chunk_handler.o build/logger.o build/rbtree.o -o $(dlib)

build/main.o: src/main.c src/logger/logger.h
		$(CC) $(CFLAGS) -c src/main.c -o build/main.o -Isrc/logger -Isrc/rbtree -Isrc/alloc

build/cmalloc.o: src/alloc/cmalloc.c src/alloc/cmalloc.h src/alloc/chunk_handler.h src/rbtree/rbtree.h
		$(CC) $(CFLAGS) -fPIC -c src/alloc/cmalloc.c -o build/cmalloc.o -Isrc/rbtree -Isrc/alloc

build/cfree.o: src/alloc/cfree.c src/alloc/cfree.h src/alloc/cmalloc.h src/rbtree/rbtree.h src/alloc/cfree.h
		$(CC) $(CFLAGS) -fPIC -c src/alloc/cfree.c -o build/cfree.o -Isrc/rbtree -Isrc/alloc

build/chunk_handler.o: src/alloc/chunk_handler.c src/alloc/chunk_handler.h src/alloc/cmalloc.h src/rbtree/rbtree.h
		$(CC) $(CFLAGS) -fPIC -c src/alloc/chunk_handler.c -o build/chunk_handler.o -Isrc/rbtree -Isrc/alloc

build/logger.o: src/logger/logger.c src/logger/logger.h src/alloc/cfree.h src/alloc/cmalloc.h
		$(CC) $(CFLAGS) -fPIC -c src/logger/logger.c -o build/logger.o -Isrc/alloc -Isrc/rbtree

build/rbtree.o: src/rbtree/rbtree.c src/rbtree/rbtree.h src/alloc/cmalloc.h
		$(CC) $(CFLAGS) -fPIC -c src/rbtree/rbtree.c -o build/rbtree.o -Isrc/alloc 

dir:
	@mkdir bin
	@mkdir dlib
	@mkdir build
		
clean:
	@rm bin/*
	@rm dlib/*
	@rm build/*