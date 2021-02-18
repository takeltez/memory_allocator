#include "logger.h"
#include "my_free.h"
#include "my_malloc.h"

extern rbtree *tree;
extern rbtree *null_node;

void rbtree_print(rbtree *root)
{
	mem_chunk chunk;

	if (root && root != null_node)
	{
		chunk = *root->chunk_ptr;

		printf("meta segment: [%p]\nchunk size(node): %ld\nis used: %u\nuser segment: [%p]\nparent node: %ld\nleft node: %ld\nright node: %ld\n\n", 
													chunk.ptr, *chunk.size, *chunk.is_used, chunk.ptr + OFFSET_TO_USER_SEG, 
														rbtree_key(root->parent), rbtree_key(root->left), rbtree_key(root->right));
		
		rbtree_print(root->left);
		rbtree_print(root->right);
	}
}

void test(void)
{
	void *first = my_malloc(100);
	void *second = my_malloc(10);
	void *third = my_malloc(50);
	void *fourth = my_malloc(150);
	void *fiveth = my_malloc(40);
	void *sixth = my_malloc(30);

	printf("Chunks states before my_free:\n\n");
	rbtree_print(tree);

	my_free(second);
	my_free(third);
	my_free(fiveth);
	my_free(sixth);

	printf("\nChunks states after my_free:\n\n");
	rbtree_print(tree);

	second = my_malloc(48);
	third = my_malloc(50);
	sixth = my_malloc(39);
	fiveth = my_malloc (230);

	void *seventh = my_malloc(40);
	void *a = my_malloc(27);
	void *b = my_malloc(9);

	printf("\nChunks states after using free blocks again:\n\n");
	rbtree_print(tree);
}