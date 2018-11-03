#include <mgl/container/singly_linked_list.h>

typedef struct
{
	mgl_singly_linked_list_node_t* node;
	mgl_singly_linked_list_t* list;
} mgl_singly_linked_list_iterator_t;

MGL_STATIC_ASSERT(sizeof(mgl_singly_linked_list_iterator_t) <= MGL_ITERATOR_AVAILABLE_SIZE, "singly_linked_list iterator too big");

static mgl_error_t mgl_singly_linked_list_iterator_next(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	out->functions = it->functions;
	
	if (((mgl_singly_linked_list_iterator_t*)it->data)->node == NULL || ((mgl_singly_linked_list_iterator_t*)it->data)->node->next == NULL)
	{
		((mgl_singly_linked_list_iterator_t*)out->data)->node = NULL;
		((mgl_singly_linked_list_iterator_t*)out->data)->list = ((mgl_singly_linked_list_iterator_t*)it->data)->list;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}

	((mgl_singly_linked_list_iterator_t*)out->data)->node = ((mgl_singly_linked_list_iterator_t*)it->data)->node->next;
	((mgl_singly_linked_list_iterator_t*)out->data)->list = ((mgl_singly_linked_list_iterator_t*)it->data)->list;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_singly_linked_list_iterator_move(const mgl_iterator_t * it, mgl_iterator_t * out, mgl_i64_t move)
{
	out->functions = it->functions;
	if (move < 0)
		return MGL_ERROR_UNSUPPORTED;	

	((mgl_singly_linked_list_iterator_t*)out->data)->list = ((mgl_singly_linked_list_iterator_t*)it->data)->list;
	mgl_singly_linked_list_node_t* node = ((mgl_singly_linked_list_iterator_t*)it->data)->node;

	for (; move > 0; --move)
	{
		node = node->next;
		if (node == NULL)
		{
			((mgl_singly_linked_list_iterator_t*)out->data)->node = NULL;
			return MGL_ERROR_OUT_OF_BOUNDS;
		}
	}

	((mgl_singly_linked_list_iterator_t*)out->data)->node = node;
	return MGL_ERROR_NONE;
}

static mgl_bool_t mgl_singly_linked_list_iterator_is_null(const mgl_iterator_t * it)
{
	return ((mgl_singly_linked_list_iterator_t*)it->data)->node == NULL;
}

static void * mgl_singly_linked_list_iterator_get(const mgl_iterator_t * it)
{
	MGL_ASSERT(!mgl_singly_linked_list_iterator_is_null(it));
	return (mgl_u8_t*)((mgl_singly_linked_list_iterator_t*)it->data)->node - sizeof(mgl_singly_linked_list_node_t) - ((mgl_singly_linked_list_iterator_t*)it->data)->list->element_size;
}

static void * mgl_singly_linked_list_iterator_get_raw(const mgl_iterator_t * it)
{
	if ((mgl_u8_t*)((mgl_singly_linked_list_iterator_t*)it->data)->node == NULL)
		return NULL;
	return (mgl_u8_t*)((mgl_singly_linked_list_iterator_t*)it->data)->node - sizeof(mgl_singly_linked_list_node_t) - ((mgl_singly_linked_list_iterator_t*)it->data)->list->element_size;
}

static mgl_iterator_functions_t mgl_singly_linked_list_iterator_functions =
{
	&mgl_singly_linked_list_iterator_next,
	NULL,
	&mgl_singly_linked_list_iterator_move,
	&mgl_singly_linked_list_iterator_is_null,
	&mgl_singly_linked_list_iterator_get,
	&mgl_singly_linked_list_iterator_get_raw,
};

void MGL_API mgl_init_singly_linked_list(mgl_singly_linked_list_t * list, mgl_u64_t element_count, mgl_u64_t element_size, mgl_allocator_t * allocator)
{
	MGL_DEBUG_ASSERT(list != NULL && element_size > 0 && allocator != NULL);

	list->element_count = element_count;
	list->element_size = element_size;
	list->first_node = NULL;
	list->allocator = allocator;
}

void MGL_API mgl_terminate_singly_linked_list(mgl_singly_linked_list_t * list)
{
	MGL_DEBUG_ASSERT(list != NULL);
	
	mgl_singly_linked_list_node_t* node = list->first_node;
	while (node != NULL)
	{
		mgl_singly_linked_list_node_t* next = node->next;
		mgl_deallocate(list->allocator, node - sizeof(mgl_singly_linked_list_node_t) - list->element_size);
		node = next;
	}

	list->first_node = NULL;
}

void MGL_API mgl_get_singly_linked_list_begin_it(mgl_singly_linked_list_t * list, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(list != NULL && it != NULL);
	it->functions = &mgl_singly_linked_list_iterator_functions;
	((mgl_singly_linked_list_iterator_t*)it->data)->list = list;
	((mgl_singly_linked_list_iterator_t*)it->data)->node = list->first_node;
}

void MGL_API mgl_get_singly_linked_list_end_it(mgl_singly_linked_list_t * list, mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(list != NULL && it != NULL);
	it->functions = &mgl_singly_linked_list_iterator_functions;
	((mgl_singly_linked_list_iterator_t*)it->data)->list = list;
	((mgl_singly_linked_list_iterator_t*)it->data)->node = list->first_node;
	if (list->first_node != NULL)
		while (((mgl_singly_linked_list_iterator_t*)it->data)->node->next != NULL)
			((mgl_singly_linked_list_iterator_t*)it->data)->node = ((mgl_singly_linked_list_iterator_t*)it->data)->node->next;
}

