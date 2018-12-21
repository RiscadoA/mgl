#include <mgl/thread/atomic.h>

#ifndef __STDC_NO_ATOMICS__
#include <stdatomic.h>

static void* mgl_align_pointer(void* ptr, mgl_u64_t alignment)
{
	return (void*)(((mgl_uptr_t)ptr + (mgl_uptr_t)alignment - 1) & ~(mgl_uptr_t)(alignment - 1));
}

void MGL_API mgl_store_atomic_i8(mgl_atomic_i8_t * dst, mgl_i8_t src)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i8_t* ptr = (_Atomic mgl_i8_t*)&dst->data[0];
    atomic_store(ptr, src);
}

mgl_i8_t MGL_API mgl_load_atomic_i8(mgl_atomic_i8_t * src)
{
	MGL_DEBUG_ASSERT(src != NULL);
    _Atomic mgl_i8_t* ptr = (_Atomic mgl_i8_t*)&src->data[0];
    return atomic_load(ptr);
}

void MGL_API mgl_and_atomic_i8(mgl_atomic_i8_t * dst, mgl_i8_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	_Atomic mgl_i8_t* ptr = (_Atomic mgl_i8_t*)&dst->data[0];
    atomic_fetch_and(ptr, value);
}

void MGL_API mgl_or_atomic_i8(mgl_atomic_i8_t * dst, mgl_i8_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i8_t* ptr = (_Atomic mgl_i8_t*)&dst->data[0];
    atomic_fetch_or(ptr, value);
}

void MGL_API mgl_xor_atomic_i8(mgl_atomic_i8_t * dst, mgl_i8_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i8_t* ptr = (_Atomic mgl_i8_t*)&dst->data[0];
    atomic_fetch_xor(ptr, value);
}

void MGL_API mgl_store_atomic_i16(mgl_atomic_i16_t * dst, mgl_i16_t src)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i16_t* ptr = (_Atomic mgl_i16_t*)&dst->data[0];
    atomic_store(ptr, src);
}

mgl_i16_t MGL_API mgl_load_atomic_i16(mgl_atomic_i16_t * src)
{
	MGL_DEBUG_ASSERT(src != NULL);
     _Atomic mgl_i16_t* ptr = (_Atomic mgl_i16_t*)&src->data[0];
    return atomic_load(ptr);
}

mgl_i16_t MGL_API mgl_increment_atomic_i16(mgl_atomic_i16_t * dst)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i16_t* ptr = (_Atomic mgl_i16_t*)&dst->data[0];
    atomic_fetch_add(ptr, 1);
}

mgl_i16_t MGL_API mgl_decrement_atomic_i16(mgl_atomic_i16_t * dst)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i16_t* ptr = (_Atomic mgl_i16_t*)&dst->data[0];
    atomic_fetch_sub(ptr, 1);
}

void MGL_API mgl_and_atomic_i16(mgl_atomic_i16_t * dst, mgl_i16_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i16_t* ptr = (_Atomic mgl_i16_t*)&dst->data[0];
    atomic_fetch_and(ptr, value);
}

void MGL_API mgl_or_atomic_i16(mgl_atomic_i16_t * dst, mgl_i16_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i16_t* ptr = (_Atomic mgl_i16_t*)&dst->data[0];
    atomic_fetch_or(ptr, value);
}

void MGL_API mgl_xor_atomic_i16(mgl_atomic_i16_t * dst, mgl_i16_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i16_t* ptr = (_Atomic mgl_i16_t*)&dst->data[0];
    atomic_fetch_xor(ptr, value);
}

void MGL_API mgl_store_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t src)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i32_t* ptr = (_Atomic mgl_i32_t*)&dst->data[0];
    atomic_store(ptr, src);
}

mgl_i32_t MGL_API mgl_load_atomic_i32(mgl_atomic_i32_t * src)
{
	MGL_DEBUG_ASSERT(src != NULL);
    _Atomic mgl_i32_t* ptr = (_Atomic mgl_i32_t*)&src->data[0];
    return atomic_load(ptr);
}

mgl_i32_t MGL_API mgl_increment_atomic_i32(mgl_atomic_i32_t * dst)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i32_t* ptr = (_Atomic mgl_i32_t*)&dst->data[0];
    atomic_fetch_add(ptr, 1);
}

mgl_i32_t MGL_API mgl_decrement_atomic_i32(mgl_atomic_i32_t * dst)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i32_t* ptr = (_Atomic mgl_i32_t*)&dst->data[0];
    atomic_fetch_sub(ptr, 1);
}

void MGL_API mgl_add_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i32_t* ptr = (_Atomic mgl_i32_t*)&dst->data[0];
    atomic_fetch_add(ptr, value);
}

void MGL_API mgl_and_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i32_t* ptr = (_Atomic mgl_i32_t*)&dst->data[0];
    atomic_fetch_and(ptr, value);
}

void MGL_API mgl_or_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i32_t* ptr = (_Atomic mgl_i32_t*)&dst->data[0];
    atomic_fetch_or(ptr, value);
}

void MGL_API mgl_xor_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
    _Atomic mgl_i32_t* ptr = (_Atomic mgl_i32_t*)&dst->data[0];
    atomic_fetch_xor(ptr, value);
}

#endif // __STDC_NO_ATOMICS__
