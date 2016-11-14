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
					std::function<void()> func;
					{
						std::unique_lock<std::mutex> l(threadpool->lock);
						threadpool->condition.wait(l, [&](){return !threadpool->functions.empty() || !threadpool->run;});
						if (!threadpool->run) return;

						func = threadpool->functions.front();
						threadpool->functions.pop();
					}
					func();
				}
			}
		};



		std::vector<std::thread> threads;
		std::queue<std::function<void()> > functions;

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
			 	functions.push(_func);
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
