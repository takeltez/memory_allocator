#include "rbtree.h"
#include "cmalloc.h"

rbtree *null_node;

rbtree *add_chunk(rbtree *root, mem_chunk *chunk_ptr)
{
	rbtree *new_node = root, *parent_node = null_node;

	while(new_node != null_node && new_node)
	{
		parent_node = new_node;

		if(*chunk_ptr->size < new_node->chunk_size)
		{
			if(*chunk_ptr->size >= new_node->chunk_size - DEVIATION)
			{
				if(new_node->chunks_array_size < EQ_CHUNKS_COUNT)
				{
					new_node->chunks[new_node->chunks_array_size] = chunk_ptr;

					++new_node->chunks_array_size;

					return root;
				}

				return NULL;
			}

			else if(*chunk_ptr->size < new_node->chunk_size - DEVIATION)
			{
				new_node = new_node->left;
			}
		}

		else if(*chunk_ptr->size > new_node->chunk_size)
		{
			new_node = new_node->right;
		}

		else if(*chunk_ptr->size == new_node->chunk_size)
		{	
			if(new_node->chunks_array_size < EQ_CHUNKS_COUNT)
			{
				new_node->chunks[new_node->chunks_array_size] = chunk_ptr;

				++new_node->chunks_array_size;

				return root;
			}

			return NULL;
		}
	}

	new_node = (rbtree*)malloc(sizeof(rbtree));

	if(!new_node)
	{
		return NULL;
	}

	new_node->chunk_size = *chunk_ptr->size;
	new_node->chunks_array_size = 1;
	new_node->chunks[0] = chunk_ptr;
	new_node->color = NODE_RED;
	new_node->parent = parent_node;
	new_node->left = null_node;
	new_node->right = null_node;

	if(parent_node != null_node) 
	{	
		if(*chunk_ptr->size < parent_node->chunk_size) 
		{	
			parent_node->left = new_node;
		}
		else
		{
			parent_node->right = new_node;
		}
	}
	else 
	{
		root = new_node;
	}

	return rbtree_fixup(root, new_node); 
}

mem_chunk *free_chunk_lookup(rbtree *root, size_t size)
{
	if(!root || root == null_node)
	{	
		return NULL;
	}

	while(root && root != null_node)
	{		
		if(size < root->chunk_size)
		{	
			if(size >= root->chunk_size - DEVIATION)
			{
				for (size_t i = 0; i < root->chunks_array_size; ++i)
				{
					if(size <= *root->chunks[i]->size && !(*root->chunks[i]->is_used))
					{
						return root->chunks[i];
					}
				}
		
				root = root->right;

			}

			else if(size < root->chunk_size - DEVIATION)
			{
				root = root->left;
			}
		}

		else if(size > root->chunk_size)
		{
			root = root->right;
		}

		else if(size == root->chunk_size)
		{
			for (size_t i = 0; i < root->chunks_array_size; ++i)
			{
				if(size <= *root->chunks[i]->size && !(*root->chunks[i]->is_used))
				{
					return root->chunks[i];
				}
			}

			root = root->right;
		}
	}
	
	return NULL;
}

rbtree *rbtree_fixup(rbtree *root, rbtree *curr_node)
{
	rbtree *uncle_node;
			
	while(curr_node != root && curr_node->parent->color == NODE_RED) 
	{
		if(curr_node->parent == curr_node->parent->parent->left) 
		{
			uncle_node = curr_node->parent->parent->right; 

			if(uncle_node->color == NODE_RED) 
			{
				curr_node->parent->color = NODE_BLACK;
				uncle_node->color = NODE_BLACK;
				curr_node->parent->parent->color = NODE_RED;
				curr_node = curr_node->parent->parent;
			}
			else
			{
				if(curr_node == curr_node->parent->right) 
				{
					curr_node = curr_node->parent;
					root = rbtree_left_rotate(root, curr_node);
				}
			
				curr_node->parent->color = NODE_BLACK;
				curr_node->parent->parent->color = NODE_RED;
				root = rbtree_right_rotate(root, curr_node->parent->parent);
			}
		}
		else 
		{
			uncle_node = curr_node->parent->parent->left; 

			if(uncle_node->color == NODE_RED) 
			{
				curr_node->parent->color = NODE_BLACK;
				uncle_node->color = NODE_BLACK;
				curr_node->parent->parent->color = NODE_RED;
				curr_node = curr_node->parent->parent;
			}
			else
			{
				if(curr_node == curr_node->parent->left) 
				{
					curr_node = curr_node->parent;
					root = rbtree_right_rotate(root, curr_node);
				}
	
				curr_node->parent->color = NODE_BLACK;
				curr_node->parent->parent->color = NODE_RED;
				root = rbtree_left_rotate(root, curr_node->parent->parent);
			}
		}
	}

	root->color = NODE_BLACK;

	return root;
}

rbtree *rbtree_left_rotate(rbtree *root, rbtree *curr_node)
{
	rbtree *right_node = curr_node->right;
	
	curr_node->right = right_node->left; 
	
	if(right_node->left != null_node)
	{
		right_node->left->parent = curr_node;
	}
	
	if(right_node != null_node) 
	{
		right_node->parent = curr_node->parent;
	}
	if(curr_node->parent != null_node)
	{
		if(curr_node == curr_node->parent->left)
		{
			curr_node->parent->left = right_node;
		}
		else
		{
			curr_node->parent->right = right_node;
		}
	}
	else
	{
		root = right_node;
	}
	
	right_node->left = curr_node;
	
	if(curr_node != null_node)
	{
		curr_node->parent = right_node;
	}
	
	return root;
}

rbtree *rbtree_right_rotate(rbtree *root, rbtree *curr_node)
{
	rbtree *left_node = curr_node->left;

	curr_node->left = left_node->right;
	if(left_node->right != null_node)
	{
		left_node->right->parent = curr_node;
	}

	if(left_node != null_node) 
	{
		left_node->parent = curr_node->parent;
	}
	if(curr_node->parent != null_node)
	{
		if(curr_node == curr_node->parent->right)
		{
			curr_node->parent->right = left_node;
		}
		else
		{
			curr_node->parent->left = left_node;
		}
	}
	else
	{
		root = left_node;
	}

	left_node->right = curr_node;

	if(curr_node != null_node)
	{
		curr_node->parent = left_node;
	}

	return root;
}

size_t rbtree_key(rbtree *node)
{
	if(!node || node == null_node)
	{
		return -1;
	}

	return node->chunk_size;
}
