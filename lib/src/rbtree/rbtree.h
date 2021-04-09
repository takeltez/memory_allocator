#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "cmalloc.h"

#define NODE_RED 1
#define NODE_BLACK 0

#define EQ_CHUNKS_COUNT 10

typedef struct rbtree
{
	size_t chunk_size;
	size_t filled_elems_count;
	mem_chunk *chunks[EQ_CHUNKS_COUNT];
	uint32_t color;
	struct rbtree *parent;
	struct rbtree *left;
	struct rbtree *right;
} rbtree;

rbtree *rbtree_add(rbtree *root, mem_chunk *chunk_ptr);
mem_chunk *rbtree_lookup_freed_chunk(rbtree *root, size_t size);
mem_chunk *rbtree_lookup_chunk_for_free(rbtree *root, size_t size, void *ptr);

rbtree *rbtree_add_fixup(rbtree *root, rbtree *curr_node);
rbtree *rbtree_left_rotate(rbtree *root, rbtree *curr_node);
rbtree *rbtree_right_rotate(rbtree *root, rbtree *curr_node);

size_t rbtree_key(rbtree *node);

