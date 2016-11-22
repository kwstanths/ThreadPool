#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

#include "Task.hpp"

namespace mns{

namespace ThreadPool {

	class ThreadPool{

		class Worker{
			ThreadPool * threadpool;
		public:
			Worker(ThreadPool * _threadpool);

			void run();
		};

		std::vector<std::thread> threads;
		std::queue<Task *> tasks;

		std::mutex lock;
		std::condition_variable condition;
		std::atomic<bool> run;
		std::atomic<bool> finish_when_done;

		std::atomic<int> total_time;
	public:
		ThreadPool(int num_threads);

		void schedule(std::function<void()> _func);

		void wait_finish();

		void stop();

		int gettime();
	};
}

}
#endif
