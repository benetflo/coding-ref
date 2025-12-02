#ifndef EMBEDDED_ARENA_H
#define EMBEDDED_ARENA_H

#include <stdlib.h> // For size_t

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
// arena_alloc
// =======================================================================
// Allocates a block of memory from the arena.
// Parameters:
//   a          - pointer to the Arena_t
//   alloc_size - number of bytes to allocate
// Returns:
//   pointer to the allocated memory, or NULL if there is not enough space
//
// NOTE: This function does not perform type checking or alignment.
//       Cast the returned pointer as needed.
// =======================================================================
static inline void * arena_alloc(Arena_t * a, size_t alloc_size)
{
    // Check if there is enough space left in the arena
    if ((a->offset + alloc_size) > a->buffer_size)
    {
        return NULL; // Return NULL if the buffer is full
    }

    // Compute the pointer to the next free memory block
    unsigned char * ptr = a->buffer_start + a->offset;

    // Update the offset for the next allocation
    a->offset += alloc_size;

    // Return the pointer to the allocated memory
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


//TODO: Alignment