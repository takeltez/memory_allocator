#include "rbtree.h"
#include "cmalloc.h"

rbtree *null_node;

rbtree *rbtree_add(rbtree *root, mem_chunk *chunk_ptr)
{
	rbtree *new_node = root, *parent_node = null_node;

	//Находим позицию для вставки нового нода
	while (new_node != null_node && new_node) //Только если дерево уже существует
	{
		parent_node = new_node;

		if (*chunk_ptr->size < new_node->chunk_size)
		{
			if (*chunk_ptr->size >= new_node->chunk_size - DEVIATION)
			{
				if (new_node->filled_elems_count < EQ_CHUNKS_COUNT)
				{
					new_node->chunks[new_node->filled_elems_count] = chunk_ptr;

					++new_node->filled_elems_count;

					return root;
				}

				new_node = new_node->right;
			}

			else if (*chunk_ptr->size < new_node->chunk_size - DEVIATION)
			{
				new_node = new_node->left;
			}
		}

		else if (*chunk_ptr->size > new_node->chunk_size)
		{
			new_node = new_node->right;
		}

		else if (*chunk_ptr->size == new_node->chunk_size)
		{	
			if (new_node->filled_elems_count < EQ_CHUNKS_COUNT)
			{
				new_node->chunks[new_node->filled_elems_count] = chunk_ptr;

				++new_node->filled_elems_count;

				return root;
			}
		}
	}

	new_node = (rbtree*)malloc(sizeof(rbtree)); //Выделяем память на нод

	if (!new_node)
	{
		return NULL;
	}

	//Инициализируем поля нода
	new_node->chunk_size = *chunk_ptr->size;
	new_node->filled_elems_count = 1;
	new_node->chunks[0] = chunk_ptr;
	new_node->color = NODE_RED;
	new_node->parent = parent_node;
	new_node->left = null_node;
	new_node->right = null_node;

	if (parent_node != null_node) //Если был создан не корень
	{	
		if (*chunk_ptr->size < parent_node->chunk_size) //То привязываем его к соответствующему предку
		{	
			parent_node->left = new_node;
		}
		else
		{
			parent_node->right = new_node;
		}
	}
	else //Иначе, созданный нод - корень
	{
		root = new_node;
	}

	return rbtree_add_fixup(root, new_node); //Восстанавление свойств
}

mem_chunk *rbtree_lookup_freed_chunk(rbtree *root, size_t size)
{
	if (!root || root == null_node)
	{	
		return NULL;
	}

	while (root && root != null_node)
	{		
		if (size < root->chunk_size)
		{	
			if (size >= root->chunk_size - DEVIATION)
			{
				for (size_t i = 0; i < root->filled_elems_count; ++i)
				{
					if (!(*root->chunks[i]->is_used))
					{
						return root->chunks[i];
					}
				}
		
				root = root->right;

			}

			else if (size < root->chunk_size - DEVIATION)
			{
				root = root->left;
			}
		}

		else if (size > root->chunk_size)
		{
			root = root->right;
		}

		else if (size == root->chunk_size)
		{
			for (size_t i = 0; i < root->filled_elems_count; ++i)
			{
				if (!(*root->chunks[i]->is_used))
				{
					return root->chunks[i];
				}
			}

			root = root->right;
		}
	}
	
	return NULL;
}

mem_chunk *rbtree_lookup_chunk_for_free(rbtree *root, size_t size, void *ptr)
{
	if (!root || root == null_node)
	{
		return NULL;
	}

	while (root && root != null_node)
	{
		if (size < root->chunk_size)
		{
			if (size >= root->chunk_size - DEVIATION)
			{
				for (size_t i = 0; i < root->filled_elems_count; ++i)
				{
					if (root->chunks[i]->ptr == ptr - USER_SEG_OFFSET)
					{
						return root->chunks[i];
					}
				}

				root = root->right;
			}

			else if (size < root->chunk_size - DEVIATION)
			{
				root = root->left;
			}
		}

		else if (size > root->chunk_size)
		{
			root = root->right;
		}
		
		else if (size == root->chunk_size)
		{
			for (size_t i = 0; i < root->filled_elems_count; ++i)
			{
				if (root->chunks[i]->ptr == ptr - USER_SEG_OFFSET)
				{
					return root->chunks[i];
				}
			}
		}
	}

	return NULL;
}

rbtree *rbtree_add_fixup(rbtree *root, rbtree *curr_node)
{
	rbtree *uncle_node;
			
	while (curr_node != root && curr_node->parent->color == NODE_RED) //Текущий нод - не корень, предок красный
	{
		if (curr_node->parent == curr_node->parent->parent->left) //Если предок слева от деда, то работаем с левым поддеревом
		{
			uncle_node = curr_node->parent->parent->right; //Находим дядю

			if (uncle_node->color == NODE_RED) //Case 1 - дядя красный
			{
				curr_node->parent->color = NODE_BLACK;
				uncle_node->color = NODE_BLACK;
				curr_node->parent->parent->color = NODE_RED;
				curr_node = curr_node->parent->parent;
			}
			else //Cases 2 & 3 - дядя черный
			{
				if (curr_node == curr_node->parent->right) //Переход от case 2 к case 3 поворотом дерева влево
				{
					curr_node = curr_node->parent;
					root = rbtree_left_rotate(root, curr_node);
				}
				//Case 3 - дядя черный, текущий узел слева от предка
				curr_node->parent->color = NODE_BLACK;
				curr_node->parent->parent->color = NODE_RED;
				root = rbtree_right_rotate(root, curr_node->parent->parent);
			}
		}
		else  //Если предок справа от деда, то работаем с правым поддеревом
		{
			uncle_node = curr_node->parent->parent->left; //Находим дядю

			if (uncle_node->color == NODE_RED) //Case 4 - дядя красный
			{
				curr_node->parent->color = NODE_BLACK;
				uncle_node->color = NODE_BLACK;
				curr_node->parent->parent->color = NODE_RED;
				curr_node = curr_node->parent->parent;
			}
			else //Cases 5 & 6 - дядя черный
			{
				if (curr_node == curr_node->parent->left) //Переход от case 5 к case 6 поворотом дерева вправо
				{
					curr_node = curr_node->parent;
					root = rbtree_right_rotate(root, curr_node);
				}
				//Case 3 - дядя черный, текущий узел справа от предка
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
	
	curr_node->right = right_node->left; // Create curr_node->right link
	
	if (right_node->left != null_node)
	{
		right_node->left->parent = curr_node;
	}
	
	if (right_node != null_node) // Create right_node->parent link
	{
		right_node->parent = curr_node->parent;
	}
	if (curr_node->parent != null_node)
	{
		if (curr_node == curr_node->parent->left)
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
	
	if (curr_node != null_node)
	{
		curr_node->parent = right_node;
	}
	
	return root;
}

rbtree *rbtree_right_rotate(rbtree *root, rbtree *curr_node)
{
	rbtree *left_node = curr_node->left;

	curr_node->left = left_node->right; // Create curr_node->left link
	if (left_node->right != null_node)
	{
		left_node->right->parent = curr_node;
	}

	if (left_node != null_node) // Create left_node->parent link
	{
		left_node->parent = curr_node->parent;
	}
	if (curr_node->parent != null_node)
	{
		if (curr_node == curr_node->parent->right)
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

	if (curr_node != null_node)
	{
		curr_node->parent = left_node;
	}

	return root;
}

size_t rbtree_key(rbtree *node)
{
	if (!node || node == null_node)
	{
		return -1;
	}

	return node->chunk_size;
}
