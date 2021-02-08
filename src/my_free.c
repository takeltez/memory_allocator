#include "my_free.h"
#include "my_malloc.h"

extern uint32_t call_ind;

void my_free(void *ptr)
{
	for (size_t i = 0; i < call_ind; ++i)
	{
		if (chunk_list[i].ptr == ptr - OFFSET_TO_USER_SEG)
		{
			*chunk_list[i].is_used = 0;

			 size_t *item = (size_t*)ptr;
			 
			 *item = 0;

			 ptr = NULL;
		}
	}
}