#include <iostream>
#include "matvec.h"

int main(){

matrix<double> a(190,190);
matrix<double> b(190,190);
a = 0.045;
b = 0.055;
clock_t start_t = clock();

for(int i=0; i<100; i++)
	a = a & b;

clock_t end_t = clock();
printf("Execution time: %f seconds\n", ((double)(end_t - start_t)) / CLOCKS_PER_SEC);
	return 0;
}
