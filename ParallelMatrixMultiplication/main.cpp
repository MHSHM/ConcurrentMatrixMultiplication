#include <iostream>
#include "Matrix.h"
#include "ThreadPool.h"
#include "Task.h"

int main()
{
	ThreadPool pool(7);
	Matrix<200> m, res1, res2;

	m.InitializeWithRandom();

	m.Multiply(m, res1); 
	m.ParallelMultiply(m, res2, pool);

	std::this_thread::sleep_for(std::chrono::seconds(10)); 

	std::cout << "Sequential Solution\n" << res1;
	std::cout << "\n\n\n\n"; 

	std::cout << "Parallel Solution\n" << res2 << '\n';
}