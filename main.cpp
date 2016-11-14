#include <iostream>
#include <algorithm>
#include <unistd.h>

#include "ThreadPool.hpp"

mns::ThreadPool * threadpool;

void printhi(int id)
{
	std::cout << "Hello from:" << id << std::endl;
	return;
}

void invoke1(){
	int j;

	for (j= 0; j<10; j++){
		threadpool->schedule([i]{ printhi(j); });
	}
}

void invoke2(){
	int i;

	for (i = 0; i < 10; i++) {
		threadpool->schedule([i]{ printhi(i); });
	}
}


int main(){

	threadpool = new mns::ThreadPool(2);

	std::thread t1 = std::thread(invoke1);
	std::thread t2 = std::thread(invoke2);


	usleep(100000);
	t1.join();
	t2.join();
	threadpool->wait();

	return 0;
}
