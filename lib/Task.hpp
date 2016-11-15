#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <iostream>
#include <sched.h>
#include <string.h>
#include <functional>
#include <sys/time.h>

namespace mns{

	class Task{
      private:
            std::function<void()> func;
		int time;

      public:
            Task(std::function<void()> _func);

            void operator()();

		int gettime();
      };

}

#endif
