#include "Task.hpp"

namespace mns{

      Task::Task(std::function<void()> _func): func(_func){
            time = 0;
      };

      void Task::operator()(){
            struct timeval time_start, time_stop;
            gettimeofday(&time_start, NULL);

            func();

            gettimeofday(&time_stop, NULL);
            time = 1000 * (time_stop.tv_sec - time_start.tv_sec) + (time_stop.tv_usec - time_start.tv_usec) / 1000;
      }

      int Task::gettime(){
            return time;
      }

}