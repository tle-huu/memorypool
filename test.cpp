#include "Memorypool.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <time.h>
#include <vector>


double GetTickCount(void) 
{
  struct timespec now;

    if (clock_gettime(CLOCK_MONOTONIC, &now))
		return 0;
	return now.tv_sec * 1000  + now.tv_nsec / 1000000.0;
}



int main()
{

	Memorypool		pool(5000, 100000);

	std::vector<void*>		vector(100000);

	clock_t		start = clock();

	for (int i = 0; i < 100000; i++)
		vector[i] = pool.alloc(5000);


	std::cout << "Using memory pool : " << (((double)clock() - start) / CLOCKS_PER_SEC) << std::endl << std::endl;


	start = clock();

	for (int i= 0; i < 100000;i++)
		malloc(5000);

	std::cout << "Without using memory pool : " << (((double)clock() - start) / CLOCKS_PER_SEC) << std::endl << std::endl;

	return 0;
}
