#ifndef EMBEDDED_ARENA_H
#define EMBEDDED_ARENA_H

#include <stdlib.h> // For size_t

// NOTE: Alignment may introduce padding between allocations.
// For example, allocating a char followed by an int may leave unused bytes
// to ensure the int starts at a 4-byte aligned address.
// To reduce wasted space, consider allocating larger types first, then smaller ones.

// NOTE: Each data type must be allocated at an offset that is a multiple of its size.
// For example, a 4-byte int must start at an offset divisible by 4, a 2-byte short at an offset divisible by 2, etc.
// This ensures correct alignment for the CPU and avoids crashes or slow memory access.


// =======================================================================
// Arena_t
// =======================================================================
// Structure representing a simple memory arena (fast, linear allocator)
// =======================================================================
typedef struct
{
    unsigned char * buffer_start; // Pointer to the first byte of the buffer
    size_t buffer_size;           // Total size of the buffer in bytes
    size_t offset;                // Number of bytes already allocated
} Arena_t;

// =======================================================================
// arena_init
// =======================================================================
// Initializes the arena with a given buffer and size.
// Parameters:
//   a           - pointer to the Arena_t to initialize
//   buffer_ptr  - pointer to an already allocated buffer (static or dynamic)
//   buffer_size - size of the buffer in bytes
// =======================================================================
static inline void arena_init(Arena_t * a, unsigned char * buffer_ptr, size_t buffer_size)
{
    a->buffer_start = buffer_ptr;  // Set pointer to the start of the buffer
    a->buffer_size = buffer_size;  // Set total buffer size
    a->offset = 0;                 // No bytes have been allocated yet
}

// =======================================================================
// align_offset
// =======================================================================
// Helper function to round the offset up to the next multiple of alignment.
// Parameters:
//   offset    - current offset in the arena
//   alignment - desired alignment (must be power of 2, e.g., 1, 2, 4, 8)
// Returns:
//   aligned offset
// =======================================================================
static inline size_t align_offset(size_t offset, size_t alignment)
{
    return (offset + (alignment - 1)) & ~(alignment - 1);
}

// =======================================================================
// arena_alloc_aligned
// =======================================================================
// Allocates a block of memory from the arena with the specified alignment.
// Parameters:
//   a          - pointer to the Arena_t
//   alloc_size - number of bytes to allocate
//   alignment  - alignment requirement (e.g., 4 for int, 8 for double)
// Returns:
//   pointer to the allocated memory, or NULL if there is not enough space
// =======================================================================
static inline void * arena_alloc_aligned(Arena_t * a, size_t alloc_size, size_t alignment)
{
    // Round current offset up to the next aligned address
    size_t aligned_offset = align_offset(a->offset, alignment);

    // Check if there is enough space in the arena
    if ((aligned_offset + alloc_size) > a->buffer_size)
    {
        return NULL; // Not enough memory
    }

    // Compute pointer to the allocated block
    unsigned char * ptr = a->buffer_start + aligned_offset;

    // Update offset for next allocation
    a->offset = aligned_offset + alloc_size;

    return ptr;
}

// =======================================================================
// arena_reset
// =======================================================================
// Resets the arena so that all memory can be reused.
// NOTE: This does not free individual objects; it simply allows the
//       entire buffer to be reused for new allocations.
// =======================================================================
static inline void arena_reset(Arena_t * a)
{
    a->offset = 0; // Reset offset back to the start
}

#endif
