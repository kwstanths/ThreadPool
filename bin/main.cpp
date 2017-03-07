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
		for(int i=0; i<loop_times_; i++);
		return;
	}

} process_t;

void invoke1(){
	int j;

	for (j= 0; j<1000; j++){
		process_t proc = process_t(1000000);
		threadpool->schedule(proc);
	}
}

void invoke2(){
	int i;

	for (i = 0; i < 1000; i++) {
		process_t proc = process_t(1000000);
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
	invoke1();
	invoke2();
	threadpool->wait_finish();

	std::cout << "Total time: " << threadpool->gettime() << std::endl;

	return 0;
}
