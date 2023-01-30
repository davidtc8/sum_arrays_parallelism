#include <iostream>
#include <omp.h>

#define N 1000 //Amount of elements handled by arrays
#define chunk 100 // Amount that every array will have per thread
#define mostrar 10 // Amount of data that will be printed

void imprimeArreglo(float * d);

int main()
{
    std::cout << "Summing arrays in parallel\n";
	float a[N], b[N], c[N]; // Declaring 3 arrays the first 2 are used to assign values and the third one will be used to store the results
	int i; 

	// The following for will create arrays of size N
	for (i = 0; i < N; i++)
	{
		a[i] = i * 10;
		b[i] = (i + 3) * 5;
	}
	int pedazos = chunk;

	// Process to create threads and execute the operations using parallelism
	// Defining that the instruction will be executed using the library OpenMP
	// Arrays are in a shared memory area sho the threads can access multiple values
	#pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)

	for (i = 0; i < N; i++)
		c[i] = a[i] + b[i];
	
	std::cout << "Printing the first " << mostrar << " values of array a: " << std::endl;
	imprimeArreglo(a);
	std::cout << "Printing the first " << mostrar << " values of array b: " << std::endl;
	imprimeArreglo(b);
	std::cout << "Printing the first " << mostrar << " values of array c: " << std::endl;
	imprimeArreglo(c);
}

void imprimeArreglo(float * d)
{
	for (int x = 0; x < mostrar; x++)
		std::cout << d[x] << " - ";
	std::cout << std::endl;
}