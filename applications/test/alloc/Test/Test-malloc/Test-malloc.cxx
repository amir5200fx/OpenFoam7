#include <iostream>
//#include <unistd.h>
#include <stdlib.h>

int main()
{
    int* ptrs[500000];

    std::cerr << "allocating ints\n";

    for (int i = 0; i < 500000; i++)
    {
        ptrs[i] = (int*)malloc(sizeof(int));
    }

    //    for (;;);

    std::cerr << "deallocating ints\n";

    for (int i = 0; i < 500000; i++)
    {
        free(ptrs[i]);
    }

    std::cerr << "allocating double\n";

    double* array = (double*)malloc(500000 * sizeof(double));

    for (;;);

    return 0;
}
