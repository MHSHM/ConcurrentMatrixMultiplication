#include <iostream>
#include "Matrix.h"
#include "ThreadPool.h"
#include "Task.h"

int main()
{
	ThreadPool pool(7);
	Matrix<10> m1, m2, res1, res2;

	// Initialize the two matrices with random values [1 - 10]
	m1.InitializeWithRandom();
	m2.InitializeWithRandom();

	auto start = std::chrono::steady_clock::now();
	m1.Multiply(m2, res1);
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << "Sequential execution time: " << std::chrono::duration <double, std::milli>(diff).count() * 1e-3 << "s" << std::endl;


	start = std::chrono::steady_clock::now();
	m1.ParallelMultiply(m2, res2, pool); 
	end = std::chrono::steady_clock::now();
	diff = end - start;
	std::cout << "Parallel execution time: " << std::chrono::duration <double, std::milli>(diff).count() * 1e-3 << "s" << std::endl;

	std::cout << "\n\n";
	std::cout << res1; 
	std::cout << "\n\n\n"; 
	std::cout << res2;

	pool.Shutdown();
}