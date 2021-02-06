#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define HEAP_SIZE 10000
#define CHUNK_COUNT 40
#define OFFSET_TO_IS_USED_SEG 4
#define OFFSET_TO_USER_SEG (8 + OFFSET_TO_IS_USED_SEG)

void *heap_start_ptr;

typedef struct chunk
{
	void *ptr;
	size_t *size;
	unsigned int *is_used;
}mem_chunk;

mem_chunk chunk_list[CHUNK_COUNT];

unsigned int count_last_free_chunks(int i);

void chunk_disp(int i, int j);
void my_free(void *ptr);
void chunk_log(void);

void *set_chunk_start_ptr(unsigned int last_free_chunks_counter);
void *elim_fragm(void);
void *my_malloc(size_t size);


