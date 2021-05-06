#include "logger.h"
#include "cfree.h"
#include "cmalloc.h"

extern rbtree *tree;
extern rbtree *null_node;

void rbtree_print(rbtree *root)
{
	if (root && root != null_node)
	{	
		printf("Key(chunks size): %ld\n", root->chunk_size);

		for (size_t i = 0; i < root->chunks_array_size; ++i)
		{
			printf("Chunk[%ld]: meta segment: [%p], user segment: [%p], size: %ld, is used: %u\n", 
				i, root->chunks[i]->ptr, root->chunks[i]->ptr + USER_SEG, *root->chunks[i]->size, *root->chunks[i]->is_used);
		}

		printf("Parent node: %ld\nLeft node: %ld\nRight node: %ld\n\n", 
				rbtree_key(root->parent), rbtree_key(root->left), rbtree_key(root->right));
		
		rbtree_print(root->left);
		rbtree_print(root->right);
	}
}

void test(void)
{
	char *arr1;
	int *arr2;
	float *arr3;
	double *arr4;

	cmalloc(5 * sizeof(char), &arr1);
	cmalloc(10 * sizeof(int), &arr2);
	cmalloc(7 * sizeof(float), &arr3);
	cmalloc(15 * sizeof(double), &arr4);

	for(size_t i = 0, j = 'a'; i < 5; ++i, ++j)
	{
		arr1[i] = j;
	}

	for(size_t i = 0; i < 10; ++i)
	{
		arr2[i] = i;
	}

	for(size_t i = 0; i < 7; ++i)
	{
		arr3[i] = i + 2.38;
	}

	for(size_t i = 0; i < 15; ++i)
	{
		arr4[i] = i - 12.38;
	}

	for(size_t i = 0; i < 5; ++i)
	{
		printf("%c ", arr1[i]);
	}

	printf("\n");	

	for(size_t i = 0; i < 10; ++i)
	{
		printf("%d ", arr2[i]);
	}

	printf("\n");

	for(size_t i = 0; i < 7; ++i)
	{

		printf("%.2f ", arr3[i]);
	}

	printf("\n");

	for(size_t i = 0; i < 15; ++i)
	{	
		printf("%.2f ", arr4[i]);
	}

	printf("\n\n---------------------------\n");

	rbtree_print(tree);

	cfree(&arr1);
	cfree(&arr3);

	printf("---------------------------\n");	

	rbtree_print(tree);	

	cmalloc(5 * sizeof(char), &arr2);
	cmalloc(7 * sizeof(float), &arr4);

	printf("---------------------------\n");

	rbtree_print(tree);
}