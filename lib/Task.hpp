#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <iostream>
#include <sched.h>
#include <string.h>
#include <functional>
#include <sys/time.h>

namespace mns{

namespace ThreadPool{

	class Task{
	private:
		std::function<void()> func;
		int time;
		bool completed;

	public:
		Task(std::function<void()> _func){
			time = 0;
	            completed = false;
			func = _func;
		}

		void operator()(){
			struct timeval time_start, time_stop;
			gettimeofday(&time_start, NULL);

			func();

			gettimeofday(&time_stop, NULL);
			time = 1000 * (time_stop.tv_sec - time_start.tv_sec) + (time_stop.tv_usec - time_start.tv_usec) / 1000;
			completed = true;
		}

		int gettime(){
			return time;
		}
	};

}

}
#endif
