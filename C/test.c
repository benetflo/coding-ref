#include "embedded_arena.h"

#define ARRAY_SIZE 10

int main()
{

    Arena_t arena;
    unsigned char buffer[1024]; // 1 KB buffer

    arena_init(&arena, buffer, sizeof(buffer));

    int * x = (int*) arena_alloc(&arena, sizeof(int));              // try to alloc integer
    int *y = (int*) arena_alloc(&arena, sizeof(int) * ARRAY_SIZE);  // try to alloc array of integers

    // value is NULL if arena has no space left
    if (x) 
    {
        *x = 42;    // assign value to x 
    }

    if (y)
    {
        for(int i = 0; i < ARRAY_SIZE; i++)
        {
            y[i] = i + 1; // fill array with numbers starting from 1.
        }
    }



    return 0;
}