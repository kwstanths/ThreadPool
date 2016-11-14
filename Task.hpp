#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <iostream>

namespace mns{

	class Task{
      private:
            std::function<void()> func;
      public:
            Task(std::function<void()> _func): func(_func){};

            void operator()(){
                  func();
            }
      };
}
#endif
