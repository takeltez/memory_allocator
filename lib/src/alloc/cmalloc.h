#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <inttypes.h>

#define HEAP_SIZE 1000000
#define CHUNK_COUNT 10000
#define REF_COUNT 10000
#define IS_USED_SEG 4
#define SIZE_SEG 8
#define USER_SEG 12
#define DEVIATION 5

typedef struct chunk
{
	void *ptr;
	size_t *size;
	uint32_t *is_used;
}mem_chunk;

mem_chunk chunk_list[CHUNK_COUNT];

size_t *references[REF_COUNT];

void count_references(void *ptr);
void cmalloc(size_t size, void *ptr);