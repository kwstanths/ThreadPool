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

	class ThreadPool{

		class Worker{
			ThreadPool * threadpool;
		public:
			Worker(ThreadPool * _threadpool): threadpool(_threadpool){};

			void run(){
				while(1){
					Task * task;
					{
						std::unique_lock<std::mutex> l(threadpool->lock);
						threadpool->condition.wait(l, [&](){return !threadpool->tasks.empty() || !threadpool->run;});
						if (!threadpool->run) return;

						task = threadpool->tasks.front();
						threadpool->tasks.pop();
					}
					(*task)();
				}
			}
		};


		std::vector<std::thread> threads;
		std::queue<Task *> tasks;

		std::mutex lock;
		std::condition_variable condition;
		std::atomic<bool> run;
	public:
		ThreadPool(int num_threads){
			for (int i = 0; i < num_threads; i++){
					threads.push_back(std::thread(&Worker::run, new Worker(this)));
			}

			run = true;
		}

		void schedule(std::function<void()> _func){
			 {
			 	std::unique_lock<std::mutex> l(lock);
			 	tasks.push(new Task(_func));
			 }
			 condition.notify_one();
		}

		void wait(){
			run = false;

			condition.notify_all();
			for (std::vector<std::thread>::iterator itr = threads.begin(); itr != threads.end(); itr++) itr->join();

			return;
		}
	};
}
#endif
