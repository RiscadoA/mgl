#include <mgl/container/doubly_linked_list.h>
#include <mgl/memory/manipulation.h>

typedef struct
{
	mgl_doubly_linked_list_node_t* node;
	mgl_doubly_linked_list_t* list;
} mgl_doubly_linked_list_iterator_t;

MGL_STATIC_ASSERT(sizeof(mgl_doubly_linked_list_iterator_t) <= MGL_ITERATOR_AVAILABLE_SIZE, "Doubly linked list iterator too big");

static mgl_error_t mgl_doubly_linked_list_iterator_next(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	out->functions = it->functions;
	
	if (((mgl_doubly_linked_list_iterator_t*)it->data)->node == NULL || ((mgl_doubly_linked_list_iterator_t*)it->data)->node->next == NULL)
	{
		((mgl_doubly_linked_list_iterator_t*)out->data)->node = NULL;
		((mgl_doubly_linked_list_iterator_t*)out->data)->list = ((mgl_doubly_linked_list_iterator_t*)it->data)->list;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}

	((mgl_doubly_linked_list_iterator_t*)out->data)->node = ((mgl_doubly_linked_list_iterator_t*)it->data)->node->next;
	((mgl_doubly_linked_list_iterator_t*)out->data)->list = ((mgl_doubly_linked_list_iterator_t*)it->data)->list;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_doubly_linked_list_iterator_prev(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	out->functions = it->functions;

	if (((mgl_doubly_linked_list_iterator_t*)it->data)->node == NULL || ((mgl_doubly_linked_list_iterator_t*)it->data)->node->prev == NULL)
	{
		((mgl_doubly_linked_list_iterator_t*)out->data)->node = NULL;
		((mgl_doubly_linked_list_iterator_t*)out->data)->list = ((mgl_doubly_linked_list_iterator_t*)it->data)->list;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}

	((mgl_doubly_linked_list_iterator_t*)out->data)->node = ((mgl_doubly_linked_list_iterator_t*)it->data)->node->prev;
	((mgl_doubly_linked_list_iterator_t*)out->data)->list = ((mgl_doubly_linked_list_iterator_t*)it->data)->list;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_doubly_linked_list_iterator_move(const mgl_iterator_t * it, mgl_iterator_t * out, mgl_i64_t move)
{
	out->functions = it->functions;

	((mgl_doubly_linked_list_iterator_t*)out->data)->list = ((mgl_doubly_linked_list_iterator_t*)it->data)->list;
	mgl_doubly_linked_list_node_t* node = ((mgl_doubly_linked_list_iterator_t*)it->data)->node;

	if (move > 0)
		for (; move > 0; --move)
		{
			node = node->next;
			if (node == NULL)
			{
				((mgl_doubly_linked_list_iterator_t*)out->data)->node = NULL;
				return MGL_ERROR_OUT_OF_BOUNDS;
			}
		}
	else
		for (; move < 0; ++move)
		{
			node = node->prev;
			if (node == NULL)
			{
				((mgl_doubly_linked_list_iterator_t*)out->data)->node = NULL;
				return MGL_ERROR_OUT_OF_BOUNDS;
			}
		}

	((mgl_doubly_linked_list_iterator_t*)out->data)->node = node;
	return MGL_ERROR_NONE;
}

static mgl_bool_t mgl_doubly_linked_list_iterator_is_null(const mgl_iterator_t * it)
{
	return ((mgl_doubly_linked_list_iterator_t*)it->data)->node == NULL;
}

static void * mgl_doubly_linked_list_iterator_get(const mgl_iterator_t * it)
{
	MGL_ASSERT(!mgl_doubly_linked_list_iterator_is_null(it));
	return (mgl_u8_t*)((mgl_doubly_linked_list_iterator_t*)it->data)->node - ((mgl_doubly_linked_list_iterator_t*)it->data)->list->element_size;
}

static void * mgl_doubly_linked_list_iterator_get_raw(const mgl_iterator_t * it)
{
	if ((mgl_u8_t*)((mgl_doubly_linked_list_iterator_t*)it->data)->node == NULL)
		return NULL;
	return (mgl_u8_t*)((mgl_doubly_linked_list_iterator_t*)it->data)->node - ((mgl_doubly_linked_list_iterator_t*)it->data)->list->element_size;
}

static mgl_iterator_functions_t mgl_doubly_linked_list_iterator_functions =
{
	&mgl_doubly_linked_list_iterator_next,
	&mgl_doubly_linked_list_iterator_prev,
	&mgl_doubly_linked_list_iterator_move,
	&mgl_doubly_linked_list_iterator_is_null,
	&mgl_doubly_linked_list_iterator_get,
	&mgl_doubly_linked_list_iterator_get_raw,
};

void MGL_API mgl_init_doubly_linked_list(mgl_doubly_linked_list_t * list, mgl_u64_t element_size, mgl_allocator_t * allocator)
{
	MGL_DEBUG_ASSERT(list != NULL && element_size > 0 && allocator != NULL);

	list->element_count = 0;
	list->element_size = element_size;
	list->first_node = NULL;
	list->end_node = NULL;
	list->allocator = allocator;
}

void MGL_API mgl_terminate_doubly_linked_list(mgl_doubly_linked_list_t * list)
{
	MGL_DEBUG_ASSERT(list != NULL);
	
	mgl_doubly_linked_list_node_t* node = list->first_node;
	while (node != NULL)
	{
		mgl_doubly_linked_list_node_t* next = node->next;
		mgl_deallocate(list->allocator, (mgl_u8_t*)node - list->element_size);
		node = next;
	}
}

void MGL_API mgl_get_doubly_linked_list_begin_it(mgl_doubly_linked_list_t * list, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(list != NULL && it != NULL);
	it->functions = &mgl_doubly_linked_list_iterator_functions;
	((mgl_doubly_linked_list_iterator_t*)it->data)->list = list;
	((mgl_doubly_linked_list_iterator_t*)it->data)->node = list->first_node;
}

void MGL_API mgl_get_doubly_linked_list_end_it(mgl_doubly_linked_list_t * list, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(list != NULL && it != NULL);
	it->functions = &mgl_doubly_linked_list_iterator_functions;
	((mgl_doubly_linked_list_iterator_t*)it->data)->list = list;
	((mgl_doubly_linked_list_iterator_t*)it->data)->node = list->end_node;
}

mgl_error_t MGL_API mgl_doubly_linked_list_push_end(mgl_doubly_linked_list_t * list, const void * data, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(list != NULL);

	void* mem;
	mgl_error_t e = mgl_allocate(list->allocator, list->element_size + sizeof(mgl_doubly_linked_list_node_t), &mem);
	if (e != MGL_ERROR_NONE)
		return e;
	mgl_doubly_linked_list_node_t* node = (mgl_doubly_linked_list_node_t*)((mgl_u8_t*)mem + list->element_size);
	node->next = NULL;
	node->prev = list->end_node;

	if (list->end_node == NULL)
	{
		list->first_node = node;
		list->end_node = node;
	}
	else
	{
		list->end_node->next = node;
		list->end_node = node;
	}

	++list->element_count;
	if (data != NULL)
		mgl_mem_copy(mem, data, list->element_size);
	if (out_ptr != NULL)
		*out_ptr = mem;

	return MGL_ERROR_NONE;
}

void MGL_API mgl_doubly_linked_list_pop_end(mgl_doubly_linked_list_t * list)
{
	MGL_DEBUG_ASSERT(list != NULL);
	MGL_ASSERT(list->end_node != NULL);

	void* mem = (mgl_u8_t*)list->end_node - sizeof(list->element_size);

	if (list->end_node == list->first_node)
	{
		list->first_node = NULL;
		list->end_node = NULL;
	}
	else
	{
		list->end_node->prev->next = NULL;
		list->end_node = list->end_node->prev;
	}

	--list->element_count;
	
	MGL_ASSERT(mgl_deallocate(list->allocator, mem) == MGL_ERROR_NONE);
}

mgl_error_t MGL_API mgl_doubly_linked_list_push_begin(mgl_doubly_linked_list_t * list, const void * data, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(list != NULL);

	void* mem;
	mgl_error_t e = mgl_allocate(list->allocator, list->element_size + sizeof(mgl_doubly_linked_list_node_t), &mem);
	if (e != MGL_ERROR_NONE)
		return e;
	mgl_doubly_linked_list_node_t* node = (mgl_doubly_linked_list_node_t*)((mgl_u8_t*)mem + list->element_size);
	node->next = list->first_node;
	node->prev = NULL;

	if (list->first_node == NULL)
	{
		list->first_node = node;
		list->end_node = node;
	}
	else
	{
		list->first_node->prev = node;
		list->first_node = node;
	}

	++list->element_count;
	if (data != NULL)
		mgl_mem_copy(mem, data, list->element_size);
	if (out_ptr != NULL)
		*out_ptr = mem;

	return MGL_ERROR_NONE;
}

void MGL_API mgl_doubly_linked_list_pop_begin(mgl_doubly_linked_list_t * list)
{
	MGL_DEBUG_ASSERT(list != NULL);
	MGL_ASSERT(list->first_node != NULL);

	void* mem = (mgl_u8_t*)list->first_node - sizeof(list->element_size);

	if (list->end_node == list->first_node)
	{
		list->first_node = NULL;
		list->end_node = NULL;
	}
	else
	{
		list->first_node = list->first_node->next;
		list->first_node->prev = NULL;
	}

	--list->element_count;

	MGL_ASSERT(mgl_deallocate(list->allocator, mem) == MGL_ERROR_NONE);
}

mgl_error_t MGL_API mgl_doubly_linked_list_insert_after(mgl_doubly_linked_list_t * list, const mgl_iterator_t * it, const void * data, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(list != NULL);

	if (((mgl_doubly_linked_list_iterator_t*)it->data)->node == NULL)
		return mgl_doubly_linked_list_push_end(list, data, out_ptr);

	void* mem;
	mgl_error_t e = mgl_allocate(list->allocator, list->element_size + sizeof(mgl_doubly_linked_list_node_t), &mem);
	if (e != MGL_ERROR_NONE)
		return e;
	mgl_doubly_linked_list_node_t* node = (mgl_doubly_linked_list_node_t*)((mgl_u8_t*)mem + list->element_size);
	node->next = ((mgl_doubly_linked_list_iterator_t*)it->data)->node->next;
	node->prev = ((mgl_doubly_linked_list_iterator_t*)it->data)->node;

	if (list->end_node == ((mgl_doubly_linked_list_iterator_t*)it->data)->node)
		list->end_node = node;
	else
		((mgl_doubly_linked_list_iterator_t*)it->data)->node->next->prev = node;
	((mgl_doubly_linked_list_iterator_t*)it->data)->node->next = node;

	++list->element_count;
	if (data != NULL)
		mgl_mem_copy(mem, data, list->element_size);
	if (out_ptr != NULL)
		*out_ptr = mem;

	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_doubly_linked_list_insert_before(mgl_doubly_linked_list_t * list, const mgl_iterator_t * it, const void * data, void ** out_ptr)
{
	MGL_DEBUG_ASSERT(list != NULL);

	if (((mgl_doubly_linked_list_iterator_t*)it->data)->node == NULL)
		return mgl_doubly_linked_list_push_begin(list, data, out_ptr);

	void* mem;
	mgl_error_t e = mgl_allocate(list->allocator, list->element_size + sizeof(mgl_doubly_linked_list_node_t), &mem);
	if (e != MGL_ERROR_NONE)
		return e;
	mgl_doubly_linked_list_node_t* node = (mgl_doubly_linked_list_node_t*)((mgl_u8_t*)mem + list->element_size);
	node->next = ((mgl_doubly_linked_list_iterator_t*)it->data)->node;

	if (list->first_node == ((mgl_doubly_linked_list_iterator_t*)it->data)->node)
	{
		node->prev = NULL;
		list->first_node = node;
	}
	else
	{
		node->prev = ((mgl_doubly_linked_list_iterator_t*)it->data)->node->prev;
		((mgl_doubly_linked_list_iterator_t*)it->data)->node->prev->next = node;
	}

	((mgl_doubly_linked_list_iterator_t*)it->data)->node->prev = node;

	++list->element_count;
	if (data != NULL)
		mgl_mem_copy(mem, data, list->element_size);
	if (out_ptr != NULL)
		*out_ptr = mem;

	return MGL_ERROR_NONE;
}

void MGL_API mgl_doubly_linked_list_remove(mgl_doubly_linked_list_t * list, const mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(list != NULL && it != NULL);
	MGL_ASSERT(!mgl_iterator_is_null(it));

	if (list->first_node == ((mgl_doubly_linked_list_iterator_t*)it->data)->node)
	{
		if (list->end_node == list->first_node)
			list->end_node = NULL;
		list->first_node = ((mgl_doubly_linked_list_iterator_t*)it->data)->node->next;
		((mgl_doubly_linked_list_iterator_t*)it->data)->node->next->prev = NULL;
	}
	else
	{
		((mgl_doubly_linked_list_iterator_t*)it->data)->node->prev->next = ((mgl_doubly_linked_list_iterator_t*)it->data)->node->next;
		if (((mgl_doubly_linked_list_iterator_t*)it->data)->node != list->end_node)
			((mgl_doubly_linked_list_iterator_t*)it->data)->node->next->prev = ((mgl_doubly_linked_list_iterator_t*)it->data)->node->prev;
		else
			list->end_node = ((mgl_doubly_linked_list_iterator_t*)it->data)->node->prev;
	}

	void* mem = (mgl_u8_t*)((mgl_doubly_linked_list_iterator_t*)it->data)->node - list->element_size;
	MGL_ASSERT(mgl_deallocate(list->allocator, mem) == MGL_ERROR_NONE);
	
	--list->element_count;
}

void MGL_API mgl_doubly_linked_list_clear(mgl_doubly_linked_list_t * list)
{
	MGL_DEBUG_ASSERT(list != NULL);

	mgl_doubly_linked_list_node_t* node = list->first_node;
	while (node != NULL)
	{
		mgl_doubly_linked_list_node_t* next = node->next;
		mgl_deallocate(list->allocator, (mgl_u8_t*)node - list->element_size);
		node = next;
	}

	list->element_count = 0;
	list->first_node = NULL;
	list->end_node = NULL;
}

void MGL_API mgl_doubly_linked_list_set(mgl_doubly_linked_list_t * list, void * data)
{
	MGL_DEBUG_ASSERT(list != NULL && data != NULL);

	mgl_doubly_linked_list_node_t* node = list->first_node;
	while (node != NULL)
	{
		void* mem = (mgl_u8_t*)node - list->element_size;
		mgl_mem_copy(mem, data, list->element_size);
		node = node->next;
	}
}
