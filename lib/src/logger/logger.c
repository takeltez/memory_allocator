#include "logger.h"
#include "my_free.h"
#include "my_malloc.h"

extern rbtree *tree;
extern rbtree *null_node;
extern uint32_t call_ind;

void rbtree_print(rbtree *root)
{
	if (root && root != null_node)
	{	
		printf("Key(chunks size): %ld\n", root->chunk_size);

		for (size_t i = 0; i < root->filled_elems_count; ++i)
		{
			printf("Chunk[%ld]: meta segment: [%p], user segment: [%p], size: %ld, is used: %u\n", 
				i, root->chunks[i]->ptr, root->chunks[i]->ptr + OFFSET_TO_USER_SEG, *root->chunks[i]->size, *root->chunks[i]->is_used);
		}

		printf("Parent node: %ld\nLeft node: %ld\nRight node: %ld\n\n", 
				rbtree_key(root->parent), rbtree_key(root->left), rbtree_key(root->right));
		
		rbtree_print(root->left);
		rbtree_print(root->right);
	}
}

void chunk_print(void)
{
	for (size_t i = 0; i < call_ind; ++i)
	{
		printf("Chunk %ld start ptr: [%p]\n", i, chunk_list[i].ptr);
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

	count_references(&first);
	count_references(&second);
	count_references(&third);
	count_references(&fourth);
	count_references(&fiveth);
	count_references(&sixth);

	printf("Chunks states before my_free:\n\n");
	
	rbtree_print(tree);

	my_free(second);
	my_free(third);
	my_free(fiveth);
	my_free(sixth);

	delete_references(&second);
	delete_references(&third);
	delete_references(&fiveth);
	delete_references(&sixth);

	printf("\nChunks states after my_free:\n\n");
	
	rbtree_print(tree);

	second = my_malloc(48);
	third = my_malloc(50);
	sixth = my_malloc(39);
	fiveth = my_malloc(230);

	count_references(&second);
	count_references(&third);
	count_references(&sixth);
	count_references(&fiveth);

	sixth = my_malloc(39);
	fiveth = my_malloc(230);

	count_references(&sixth);
	count_references(&fiveth);

	printf("\nChunks states after using freed blocks again:\n\n");
	
	rbtree_print(tree);
}