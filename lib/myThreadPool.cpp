#include "myThreadPool.hpp"

namespace mns{

	namespace ThreadPool{

		ThreadPool::Worker::Worker(ThreadPool * _threadpool): threadpool(_threadpool){

		};

		void ThreadPool::Worker::run(){
			while(1){
				Task * task;
				threadpool->available_threads_++;
				{
					std::unique_lock<std::mutex> l(threadpool->lock);
					threadpool->condition.wait(l, [&](){return !threadpool->tasks.empty() || !threadpool->run_ || threadpool->finish_when_done_;});

					if (!threadpool->run_) return;
					if (threadpool->finish_when_done_ && threadpool->tasks.empty()) return;

					task = threadpool->tasks.front();
					threadpool->tasks.pop();
				}
				threadpool->available_threads_--;
				(*task)();
				threadpool->total_time_ = threadpool->total_time_ + task->gettime();
				delete task;
			}
		}

		ThreadPool::ThreadPool(int num_threads){
			run_ = true;
			finish_when_done_ = false;
			total_time_ = 0;
			available_threads_ = 0;
			for (int i = 0; i < num_threads; i++){
				workers.push_back(std::thread(&Worker::run, new Worker(this)));
			}
		}

		void ThreadPool::schedule(std::function<void()> _func){
			{
				std::unique_lock<std::mutex> l(lock);
				tasks.push(new Task(_func));
			}
			condition.notify_all();
		}

		int ThreadPool::available_threads(){
			return available_threads_;
		}

		void ThreadPool::wait_finish(){
			finish_when_done_ = true;

			condition.notify_all();
			for (std::vector<std::thread>::iterator itr = workers.begin(); itr != workers.end(); itr++) itr->join();

			return;
		}

		void ThreadPool::stop(){
			run_ = false;

			condition.notify_all();
			for (std::vector<std::thread>::iterator itr = workers.begin(); itr != workers.end(); itr++) itr->join();

			return;
		}

		int ThreadPool::gettime(){
			return total_time_;
		}
	}

}
