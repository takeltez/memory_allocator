#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint32_t count_last_free_chunks(int32_t i);

void chunk_disp(int32_t i, int32_t j);

void *set_chunk_start_ptr(uint32_t last_free_chunks_counter);
void *elim_fragm(void);