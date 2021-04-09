#include "logger.h"
#include "cfree.h"
#include "cmalloc.h"

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
	void *first = cmalloc(100);
	void *second = cmalloc(10);
	void *third = cmalloc(50);
	void *fourth = cmalloc(150);
	void *fiveth = cmalloc(40);
	void *sixth = cmalloc(30);

	count_references(&first);
	count_references(&second);
	count_references(&third);
	count_references(&fourth);
	count_references(&fiveth);
	count_references(&sixth);

	printf("Chunks states before cfree:\n\n");
	
	rbtree_print(tree);

	cfree(second);
	cfree(third);
	cfree(fiveth);
	cfree(sixth);

	delete_references(&second);
	delete_references(&third);
	delete_references(&fiveth);
	delete_references(&sixth);

	printf("\nChunks states after cfree:\n\n");
	
	rbtree_print(tree);

	second = cmalloc(48);
	third = cmalloc(50);
	sixth = cmalloc(39);
	fiveth = cmalloc(230);

	count_references(&second);
	count_references(&third);
	count_references(&sixth);
	count_references(&fiveth);

	sixth = cmalloc(39);
	fiveth = cmalloc(230);

	count_references(&sixth);
	count_references(&fiveth);

	printf("\nChunks states after using freed blocks again:\n\n");
	
	rbtree_print(tree);
}