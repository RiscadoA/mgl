#include <mgl/thread/atomic.h>

#if defined(MGL_SYSTEM_WINDOWS) && (defined(__STDC_NO_ATOMICS__) || !defined(__STDC_VERSION__))
#include <Windows.h>
#include <process.h>

static void* mgl_align_pointer(void* ptr, mgl_u64_t alignment)
{
	return (void*)(((mgl_uptr_t)ptr + (mgl_uptr_t)alignment - 1) & ~(mgl_uptr_t)(alignment - 1));
}

void MGL_API mgl_store_atomic_i8(mgl_atomic_i8_t * dst, mgl_i8_t src)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile CHAR* r_dst = (volatile CHAR*)mgl_align_pointer(dst->data, 4);
	InterlockedExchange8(r_dst, src);
}

mgl_i8_t MGL_API mgl_load_atomic_i8(mgl_atomic_i8_t * src)
{
	MGL_DEBUG_ASSERT(src != NULL);
	volatile CHAR* r_src = (volatile CHAR*)mgl_align_pointer(src->data, 4);
	return *r_src;
}

void MGL_API mgl_and_atomic_i8(mgl_atomic_i8_t * dst, mgl_i8_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile CHAR* r_dst = (volatile CHAR*)mgl_align_pointer(dst->data, 4);
	InterlockedAnd8(r_dst, value);
}

void MGL_API mgl_or_atomic_i8(mgl_atomic_i8_t * dst, mgl_i8_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile CHAR* r_dst = (volatile CHAR*)mgl_align_pointer(dst->data, 4);
	InterlockedOr8(r_dst, value);
}

void MGL_API mgl_xor_atomic_i8(mgl_atomic_i8_t * dst, mgl_i8_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile CHAR* r_dst = (volatile CHAR*)mgl_align_pointer(dst->data, 4);
	InterlockedXor8(r_dst, value);
}

void MGL_API mgl_store_atomic_i16(mgl_atomic_i16_t * dst, mgl_i16_t src)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile SHORT* r_dst = (volatile SHORT*)mgl_align_pointer(dst->data, 4);
	InterlockedExchange16(r_dst, src);
}

mgl_i16_t MGL_API mgl_load_atomic_i16(mgl_atomic_i16_t * src)
{
	MGL_DEBUG_ASSERT(src != NULL);
	volatile SHORT* r_src = (volatile SHORT*)mgl_align_pointer(src->data, 4);
	return *r_src;
}

mgl_i16_t MGL_API mgl_increment_atomic_i16(mgl_atomic_i16_t * dst)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile SHORT* r_dst = (volatile SHORT*)mgl_align_pointer(dst->data, 4);
	return InterlockedIncrement16(r_dst);
}

mgl_i16_t MGL_API mgl_decrement_atomic_i16(mgl_atomic_i16_t * dst)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile SHORT* r_dst = (volatile SHORT*)mgl_align_pointer(dst->data, 4);
	return InterlockedDecrement16(r_dst);
}

void MGL_API mgl_and_atomic_i16(mgl_atomic_i16_t * dst, mgl_i16_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile SHORT* r_dst = (volatile SHORT*)mgl_align_pointer(dst->data, 4);
	InterlockedAnd16(r_dst, value);
}

void MGL_API mgl_or_atomic_i16(mgl_atomic_i16_t * dst, mgl_i16_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile SHORT* r_dst = (volatile SHORT*)mgl_align_pointer(dst->data, 4);
	InterlockedOr16(r_dst, value);
}

void MGL_API mgl_xor_atomic_i16(mgl_atomic_i16_t * dst, mgl_i16_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile SHORT* r_dst = (volatile SHORT*)mgl_align_pointer(dst->data, 4);
	InterlockedXor16(r_dst, value);
}

void MGL_API mgl_store_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t src)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile LONG* r_dst = (volatile LONG*)mgl_align_pointer(dst->data, 4);
	InterlockedExchange(r_dst, src);
}

mgl_i32_t MGL_API mgl_load_atomic_i32(mgl_atomic_i32_t * src)
{
	MGL_DEBUG_ASSERT(src != NULL);
	volatile LONG* r_src = (volatile LONG*)mgl_align_pointer(src->data, 4);
	return *r_src;
}

mgl_i32_t MGL_API mgl_increment_atomic_i32(mgl_atomic_i32_t * dst)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile LONG* r_dst = (volatile LONG*)mgl_align_pointer(dst->data, 4);
	return InterlockedIncrement(r_dst);
}

mgl_i32_t MGL_API mgl_decrement_atomic_i32(mgl_atomic_i32_t * dst)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile LONG* r_dst = (volatile LONG*)mgl_align_pointer(dst->data, 4);
	return InterlockedDecrement(r_dst);
}

void MGL_API mgl_add_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile LONG* r_dst = (volatile LONG*)mgl_align_pointer(dst->data, 4);
	InterlockedAdd(r_dst, value);
}

void MGL_API mgl_and_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile LONG* r_dst = (volatile LONG*)mgl_align_pointer(dst->data, 4);
	InterlockedAnd(r_dst, value);
}

void MGL_API mgl_or_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile LONG* r_dst = (volatile LONG*)mgl_align_pointer(dst->data, 4);
	InterlockedOr(r_dst, value);
}

void MGL_API mgl_xor_atomic_i32(mgl_atomic_i32_t * dst, mgl_i32_t value)
{
	MGL_DEBUG_ASSERT(dst != NULL);
	volatile LONG* r_dst = (volatile LONG*)mgl_align_pointer(dst->data, 4);
	InterlockedXor(r_dst, value);
}

#endif // MGL_SYSTEM_WINDOWS
