#ifndef MGL_CONTAINER_DOUBLY_LINKED_LIST_H
#define MGL_CONTAINER_DOUBLY_LINKED_LIST_H

#include <mgl/memory/allocator.h>
#include <mgl/container/iterator.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct mgl_doubly_linked_list_node_t mgl_doubly_linked_list_node_t;

	/// <summary>
	///		Doubly linked list node header.
	/// </summary>
	struct mgl_doubly_linked_list_node_t
	{
		mgl_doubly_linked_list_node_t* prev;
		mgl_doubly_linked_list_node_t* next;
	};

	/// <summary>
	///		Doubly linked list header.
	/// </summary>
	typedef struct
	{ 
		mgl_u64_t element_count;
		mgl_u64_t element_size;
		mgl_doubly_linked_list_node_t* first_node;
		mgl_doubly_linked_list_node_t* end_node;
		mgl_allocator_t* allocator;
	} mgl_doubly_linked_list_t;

#define MGL_DOUBLY_LINKED_LIST_NODE_SIZE(element_size) (element_size + sizeof(mgl_doubly_linked_list_node_t))

	/// <summary>
	///		Initializes a doubly linked list.
	/// </summary>
	/// <param name="arr">Doubly linked list pointer</param>
	/// <param name="element_size">Element size</param>
	/// <param name="allocator">Allocator</param>
	void MGL_API mgl_init_doubly_linked_list(mgl_doubly_linked_list_t* arr, mgl_u64_t element_size, mgl_allocator_t* allocator);

	/// <summary>
	///		Terminates a doubly linked list. O(N)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	void MGL_API mgl_terminate_doubly_linked_list(mgl_doubly_linked_list_t* list);

	/// <summary>
	///		Inits an iterator pointing to the first element of the doubly linked list. O(1)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_doubly_linked_list_begin_it(mgl_doubly_linked_list_t* list, mgl_iterator_t* it);

	/// <summary>
	///		Inits an iterator pointing to the last element of the doubly linked list. O(1)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	/// <param name="it">Out iterator</param>
	void MGL_API mgl_get_doubly_linked_list_end_it(mgl_doubly_linked_list_t* list, mgl_iterator_t* it);

	/// <summary>
	///		Pushes an element to the end of a doubly linked list. O(1)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	/// <param name="data">Element data pointer to copy from (can be set to NULL)</param>
	/// <param name="out_ptr">Out pointer to new element</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_doubly_linked_list_push_end(mgl_doubly_linked_list_t* list, const void* data, void** out_ptr);

	/// <summary>
	///		Pops an element from the end of a doubly linked list. O(1)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	void MGL_API mgl_doubly_linked_list_pop_end(mgl_doubly_linked_list_t* list);

	/// <summary>
	///		Pushes an element to the begin of a doubly linked list. O(1)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	/// <param name="data">Element data pointer to copy from (can be set to NULL)</param>
	/// <param name="out_ptr">Out pointer to new element</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_doubly_linked_list_push_begin(mgl_doubly_linked_list_t* list, const void* data, void** out_ptr);

	/// <summary>
	///		Pops an element from the begin of a doubly linked list. O(1)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	void MGL_API mgl_doubly_linked_list_pop_begin(mgl_doubly_linked_list_t* list);

	/// <summary>
	///		Inserts an element on a doubly linked list after the element which the iterator points to. O(1)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	/// <param name="it">Iterator</param>
	/// <param name="data">Element data pointer to copy from (can be set to NULL)</param>
	/// <param name="out_ptr">Out pointer to new element</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_doubly_linked_list_insert_after(mgl_doubly_linked_list_t* list, const mgl_iterator_t* it, const void* data, void** out_ptr);

	/// <summary>
	///		Inserts an element on a doubly linked list before the element which the iterator points to. O(1)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	/// <param name="it">Iterator</param>
	/// <param name="data">Element data pointer to copy from (can be set to NULL)</param>
	/// <param name="out_ptr">Out pointer to new element</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_doubly_linked_list_insert_before(mgl_doubly_linked_list_t* list, const mgl_iterator_t* it, const void* data, void** out_ptr);

	/// <summary>
	///		Removes an element on a doubly linked list which the iterator points to. O(1)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	/// <param name="it">Iterator</param>
	void MGL_API mgl_doubly_linked_list_remove(mgl_doubly_linked_list_t* list, const mgl_iterator_t* it);

	/// <summary>
	///		Clears a doubly linked list. O(N)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	void MGL_API mgl_doubly_linked_list_clear(mgl_doubly_linked_list_t* list);

	/// <summary>
	///		Sets all elements in a doubly linked list to a value. O(N)
	/// </summary>
	/// <param name="list">Doubly linked list pointer</param>
	/// <param name="data">Data to copy into every element</param>
	void MGL_API mgl_doubly_linked_list_set(mgl_doubly_linked_list_t* list, void* data);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_CONTAINER_DOUBLY_LINKED_LIST_H
