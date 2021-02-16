#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "my_malloc.h"

#define NODE_RED 1
#define NODE_BLACK 0

typedef struct rbtree
{
	mem_chunk *chunk_ptr;
	int color;
	struct rbtree *parent;
	struct rbtree *left;
	struct rbtree *right;
} rbtree;

rbtree *rbtree_add(rbtree *root, mem_chunk *chunk_ptr);
rbtree *rbtree_lookup_freed_chunk(rbtree *root, size_t size);
rbtree *rbtree_lookup_chunk_for_free(rbtree *root, size_t size, void *ptr);

rbtree *rbtree_add_fixup(rbtree *root, rbtree *curr_node);
rbtree *rbtree_left_rotate(rbtree *root, rbtree *curr_node);
rbtree *rbtree_right_rotate(rbtree *root, rbtree *curr_node);

size_t rbtree_key(rbtree *node);

