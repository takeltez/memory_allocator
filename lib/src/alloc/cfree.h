#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void delete_references(void *ptr);
void cfree(void *ptr, uint32_t flag);