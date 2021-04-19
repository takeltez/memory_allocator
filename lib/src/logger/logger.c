#include "logger.h"
#include "cfree.h"
#include "cmalloc.h"
#include <time.h>

extern rbtree *tree;
extern rbtree *null_node;

void rbtree_print(rbtree *root)
{
	if (root && root != null_node)
	{	
		printf("Key(chunks size): %ld\n", root->chunk_size);

		for (size_t i = 0; i < root->filled_elems_count; ++i)
		{
			printf("Chunk[%ld]: meta segment: [%p], user segment: [%p], size: %ld, is used: %u\n", 
				i, root->chunks[i]->ptr, root->chunks[i]->ptr + USER_SEG_OFFSET, *root->chunks[i]->size, *root->chunks[i]->is_used);
		}

		printf("Parent node: %ld\nLeft node: %ld\nRight node: %ld\n\n", 
				rbtree_key(root->parent), rbtree_key(root->left), rbtree_key(root->right));
		
		rbtree_print(root->left);
		rbtree_print(root->right);
	}
}

void test(void)
{
/*	srand(time(NULL));	

	int *ptr[1000];

	for(size_t i = 0; i < 1000; ++i)
	{
		cmalloc(rand() % 100 + 1, ptr + i);
	}

	rbtree_print(tree);*/

	void *first = NULL;
	void *second = NULL; 
	void *third = NULL; 
	void *fourth = NULL; 
	void *fiveth = NULL; 
	void *sixth = NULL;
	
	cmalloc(100, &first);
	cmalloc(10, &second);
	cmalloc(50, &third);
	cmalloc(150, &fourth);
	cmalloc(40, &fiveth);
	cmalloc(30, &sixth);

	printf("Chunks states before cfree:\n\n");
	
	rbtree_print(tree);

	cfree(&second, 0);
	cfree(&third, 0);
	cfree(&fiveth, 0);
	cfree(&sixth, 0);

	printf("\nChunks states after cfree:\n\n");
	
	rbtree_print(tree);

	cmalloc(48, &second);
	cmalloc(50, &third);
	cmalloc(230, &fiveth);
	cmalloc(39, &sixth);

	cmalloc(230, &fiveth);
	cmalloc(39, &sixth);

	printf("\nChunks states after using freed blocks again:\n\n");
	
	rbtree_print(tree);
}