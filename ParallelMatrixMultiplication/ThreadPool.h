#pragma once

#include "Task.h"

#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>

class ThreadPool 
{
public:
	ThreadPool(uint16_t N):
		m_max_threads(N)
	{
		m_avaliable_threads = std::min((unsigned int)m_max_threads,
			std::thread::hardware_concurrency()) - 1; 

		m_threads.reserve(m_avaliable_threads);

		for (int i = 0; i < m_avaliable_threads; ++i) 
		{
			m_threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
		}
	}

	void Shutdown()
	{
		m_shutdown = true; 
		
		m_cond.notify_all();

		for (int i = 0; i < m_avaliable_threads; ++i)
		{
			m_threads[i].join();
		}
	}

public:
	
	std::queue<Task>& GetTasks() { return m_tasks; }
	
	void Schedule(const Task& task) 
	{
		std::lock_guard<std::mutex> lock(m_lock); 
		m_tasks.push(task);
		m_cond.notify_one(); 
	}

private:
	void ThreadLoop() 
	{
		while (true) 
		{
			std::unique_lock<std::mutex> lock(m_lock); 

			m_cond.wait(lock, [this]() {
					return !m_tasks.empty() || m_shutdown;
				});

			if (m_shutdown && m_tasks.empty())
			{
				return; 
			}

			Task t = std::move(m_tasks.front()); 
			m_tasks.pop(); 

			lock.unlock(); 

			t();
		}
	}

private:
	uint16_t m_max_threads; 
	uint16_t m_avaliable_threads; 

public:
	std::mutex m_lock; 
	std::condition_variable m_cond; 
	std::vector<std::thread> m_threads; 
	std::queue<Task> m_tasks; 
	bool m_shutdown = false; 
};