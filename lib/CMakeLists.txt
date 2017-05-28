cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11)

set(NAME "myThreadPool")
project(${NAME})
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${PROJECT_ROOT}/cmake/Modules/)

file(GLOB ${NAME}_HEADERS *.hpp)
file(GLOB ${NAME}_SOURCES *.cpp)

add_library(${NAME} ${${NAME}_HEADERS} ${${NAME}_SOURCES})
set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS ${NAME} DESTINATION ${NAME}/lib)
install(FILES ${${NAME}_HEADERS} DESTINATION ${NAME}/include)
