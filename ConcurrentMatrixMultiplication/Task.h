#pragma once

#include <functional>

class Task 
{
public:
	Task(std::function<void(void)> _callable):
		callable(_callable)
	{
	
	}

	void operator()() 
	{
		callable();
	}

private:
	std::function<void(void)> callable; 
};