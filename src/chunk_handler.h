#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void *set_chunk_start_ptr(void);
void *free_chunks_cover(uint32_t *is_free_chunk_avl, size_t size);