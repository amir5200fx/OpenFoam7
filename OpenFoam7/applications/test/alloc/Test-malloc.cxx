//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//	int *ptrs[500000];
//
//	cerr << "allocating ints\n";
//
//	for (int i = 0; i < 500000; i++)
//	{
//		ptrs[i] = (int*)malloc(sizeof(int));
//	}
//
//	//    for (;;);
//
//	cerr << "deallocating ints\n";
//
//	for (int i = 0; i < 500000; i++)
//	{
//		free(ptrs[i]);
//	}
//
//	cerr << "allocating double\n";
//
//	double* array = (double*)malloc(500000 * sizeof(double));
//
//	for (;;);
//}