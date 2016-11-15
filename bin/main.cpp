#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sys/time.h>

#include "ThreadPool.hpp"

mns::ThreadPool * threadpool;

void printhi(int id)
{
	for(int i=0; i<1000000; i++);
	return;
}

void invoke1(){
	int j;

	for (j= 0; j<1000; j++){
		threadpool->schedule([j]{ printhi(j); });
	}
}

void invoke2(){
	int i;

	for (i = 0; i < 1000; i++) {
		threadpool->schedule([i]{ printhi(i); });
	}
}


int main(){


	threadpool = new mns::ThreadPool(2);

	std::thread t1 = std::thread(invoke1);
	std::thread t2 = std::thread(invoke2);

	t1.join();
	t2.join();
	threadpool->wait_finish();

	std::cout << "Total time: " << threadpool->gettime() << std::endl;

	return 0;
}
