cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11)


set(NAME "ThreadPoolTest")
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(CMAKE_MODULE_PATH ${PROJECT_ROOT}/cmake/Modules/)
project(${NAME})

set(ThreadPool_ROOT /usr/local/ThreadPool/)
find_package(ThreadPool REQUIRED)

include_directories(${ThreadPool_INCLUDE_DIRS})

file(GLOB ${NAME}_HEADERS *.hpp)
file(GLOB ${NAME}_SOURCES *.cpp)

add_executable(${NAME} ${${NAME}_HEADERS} ${${NAME}_SOURCES}) 

target_link_libraries(${NAME} pthread)
target_link_libraries(${NAME} ${ThreadPool_LIBRARIES})


