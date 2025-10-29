#include <stdio.h>

// array to store function pointers
void (*funcptrs[10])(void) = {0};

int counter = 0;

// Function to store function pointer to array of function pointers
void store_function_ptr(void (*user_func)(void))
{
    funcptrs[counter] = user_func;
    counter++;
}   

// Test function
void test_func(void)
{
    printf("Hello World!\n");
}

int main()
{
    store_function_ptr(test_func);
    funcptrs[0]();
    
    return 0;
}
