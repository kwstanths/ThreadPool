#include "myThreadPool.hpp"

namespace mns{

namespace ThreadPool{

      ThreadPool::Worker::Worker(ThreadPool * _threadpool): threadpool(_threadpool){

      };

	void ThreadPool::Worker::run(){
            while(1){
                  Task * task;
                  {
                        std::unique_lock<std::mutex> l(threadpool->lock);
                        threadpool->condition.wait(l, [&](){return !threadpool->tasks.empty() || !threadpool->run || threadpool->finish_when_done;});

				if (!threadpool->run) return;
				if (threadpool->finish_when_done && threadpool->tasks.empty()) return;

				task = threadpool->tasks.front();
				threadpool->tasks.pop();
			}
			(*task)();
			threadpool->total_time = threadpool->total_time + task->gettime();
			delete task;
		}
	}

      ThreadPool::ThreadPool(int num_threads){
		run = true;
		finish_when_done = false;
		total_time = 0;

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

	void ThreadPool::wait_finish(){
            finish_when_done = true;

		condition.notify_all();
		for (std::vector<std::thread>::iterator itr = workers.begin(); itr != workers.end(); itr++) itr->join();

		return;
	}

	void ThreadPool::stop(){
            run = false;

		condition.notify_all();
		for (std::vector<std::thread>::iterator itr = workers.begin(); itr != workers.end(); itr++) itr->join();

		return;
	}

	int ThreadPool::gettime(){
		return total_time;
	}
}

}
