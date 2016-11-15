cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11)

set(NAME "ThreadPool")
project(${NAME})

file(GLOB ${NAME}_HEADERS *.hpp)
file(GLOB ${NAME}_SOURCES *.cpp)

add_library(${NAME} ${${NAME}_HEADERS} ${${NAME}_SOURCES}) 

target_link_libraries(${NAME} pthread)

install(TARGETS ${NAME} DESTINATION ${NAME}/lib)
install(FILES ${${NAME}_HEADERS} DESTINATION ${NAME}/include)
