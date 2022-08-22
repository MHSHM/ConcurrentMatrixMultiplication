#include <iostream>
#include "Matrix.h"
#include "ThreadPool.h"
#include "Task.h"

int main()
{
	ThreadPool pool(7);
	Matrix<1000> m1, m2, re1, res2;

	m1.InitializeWithRandom();
	m2.InitializeWithRandom();

	auto start = std::chrono::steady_clock::now();
	m1.Multiply(m2, res2);
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	std::cout << std::chrono::duration <double, std::milli>(diff).count() * 1e-3 << "s" << std::endl;


	start = std::chrono::steady_clock::now();
	m1.ParallelMultiply(m2, res2, pool); 
	end = std::chrono::steady_clock::now();
	diff = end - start;
	std::cout << std::chrono::duration <double, std::milli>(diff).count() * 1e-3 << "s" << std::endl;

	pool.Shutdown();
}