#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sys/time.h>

#include "myThreadPool.hpp"

mns::ThreadPool::ThreadPool * threadpool;

typedef struct process{
	int loop_times_ = 0;;
	process(int loop_times){
		loop_times_ = loop_times;
	}
	void operator()(){
		for(int i=0; i<loop_times_; i++) sleep(1);
		return;
	}

} process_t;

void invoke(){
	int j;

	for (j= 0; j<1; j++){
		process_t proc = process_t(10);
		threadpool->schedule(proc);
	}
}

int main(){
	threadpool = new mns::ThreadPool::ThreadPool(2);

	// std::thread t1 = std::thread(invoke1);
	// std::thread t2 = std::thread(invoke2);
	//
	// t1.join();
	// t2.join();
	invoke();
	sleep(1);
	std::cout << threadpool->available_threads() << std::endl;
	invoke();
	sleep(1);
	std::cout << threadpool->available_threads() << std::endl;
	threadpool->wait_finish();

	std::cout << "Total time: " << threadpool->gettime() << std::endl;

	return 0;
}
