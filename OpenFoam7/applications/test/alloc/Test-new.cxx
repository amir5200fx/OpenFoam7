//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//	int* intPtrs[500000];
//
//	cerr << "allocating ints\n";
//
//	for (int i = 0; i < 500000; i++)
//	{
//		intPtrs[i] = new int[1];
//	}
//
//	cerr << "allocated ints\n";
//
//	cerr << "deallocating ints\n";
//
//	for (int i = 0; i < 500000; i++)
//	{
//		delete[] intPtrs[i];
//	}
//
//	cerr << "deallocated ints\n";
//
//	cerr << "alloacting doubles\n";
//
//	double* doubles = new double[500000];
//
//	for (;;);
//}