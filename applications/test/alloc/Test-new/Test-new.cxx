#include <iostream>

int main()
{
    int* intPtrs[500000];

    std::cerr << "allocating ints\n";

    for (int i = 0; i < 500000; i++)
    {
        intPtrs[i] = new int[1];
    }

    std::cerr << "allocated ints\n";

    std::cerr << "deallocating ints\n";

    for (int i = 0; i < 500000; i++)
    {
        delete[] intPtrs[i];
    }

    std::cerr << "deallocated ints\n";

    std::cerr << "alloacting doubles\n";

    double* doubles = new double[500000];

    for (;;);

    return 0;
}
