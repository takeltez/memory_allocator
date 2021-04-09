#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <inttypes.h>

#define HEAP_SIZE 10000
#define CHUNK_COUNT 40
#define OFFSET_TO_SIZE_SEG 8
#define OFFSET_TO_IS_USED_SEG 4
#define OFFSET_TO_USER_SEG (OFFSET_TO_SIZE_SEG + OFFSET_TO_IS_USED_SEG)
#define DEVIATION 5
#define REF_COUNT 20

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