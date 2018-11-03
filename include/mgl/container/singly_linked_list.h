#ifndef MGL_CONTAINER_SINGLY_LINKED_LIST_H
#define MGL_CONTAINER_SINGLY_LINKED_LIST_H

#include <mgl/memory/allocator.h>
#include <mgl/container/iterator.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		Singly linked list node header.
	/// </summary>
	typedef struct
	{
		mgl_singly_linked_list_node_t* next;
	} mgl_singly_linked_list_node_t;

	/// <summary>
	///		Singly linked list header.
	/// </summary>
	typedef struct
	{ 
		mgl_u64_t element_count;
		mgl_u64_t element_size;
		mgl_singly_linked_list_node_t* first_node;
		mgl_allocator_t* allocator;
	} mgl_singly_linked_list_t;

	/// <summary>
	///		Initializes a singly linked list.
	/// </summary>
	/// <param name="arr">Singly linked list pointer</param>
	/// <param name="element_count">Element count</param>
	/// <param name="element_size">Element size</param>
	/// <param name="allocator">Allocator</param>
	void MGL_API mgl_init_singly_linked_list(mgl_singly_linked_list_t* arr, mgl_u64_t element_count, mgl_u64_t element_size, mgl_allocator_t* allocator);

	/// <summary>
	///		Terminates a singly linked list.
	/// </summary>
	/// <param name="list">Singly linked list pointer</param>
	void MGL_API mgl_terminate_singly_linked_list(mgl_singly_linked_list_t* list);

	/// <summary>
	///		Inits an iterator pointing to the first element of the singly linked list.
	/// </summary>
	/// <param name="list">Singly linked list pointer</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_singly_linked_list_begin_it(mgl_singly_linked_list_t* list, mgl_iterator_t* it);

	/// <summary>
	///		Inits an iterator pointing to the last element of the singly linked list.
	/// </summary>
	/// <param name="list">Singly linked list pointer</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_singly_linked_list_end_it(mgl_singly_linked_list_t* list, mgl_iterator_t* it);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_CONTAINER_SINGLY_LINKED_LIST_H
