#include "embedded_arena.h"
#include <stdio.h> // only for demonstration, optional

#define ARRAY_SIZE 10

int main()
{
    Arena_t arena;
    unsigned char buffer[1024]; // 1 KB buffer

    // Initialize the arena
    arena_init(&arena, buffer, sizeof(buffer));

    // Allocate an int aligned to 4 bytes
    int *x = (int*) arena_alloc_aligned(&arena, sizeof(int), sizeof(int));

    // Allocate an array of 10 ints aligned to 4 bytes
    int *y = (int*) arena_alloc_aligned(&arena, sizeof(int) * ARRAY_SIZE, sizeof(int));

    // Check if allocation succeeded
    if (x)
    {
        *x = 42; // assign value to x
        printf("x = %d\n", *x);
    }

    if (y)
    {
        for(int i = 0; i < ARRAY_SIZE; i++)
        {
            y[i] = i + 1; // fill array with numbers starting from 1
            printf("y[%d] = %d\n", i, y[i]);
        }
    }

    // Reset the arena when done (optional)
    arena_reset(&arena);

    return 0;
}
