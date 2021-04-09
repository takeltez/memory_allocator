#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define REF_COUNT 20

size_t *references[REF_COUNT];
size_t *ref_vals[REF_COUNT];

void delete_references(void *ptr);
void count_references(void *ptr);
void cfree(void *ptr);