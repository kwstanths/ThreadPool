cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11)

set(LIBNAME "myThreadPool")
project(${LIBNAME})

file(GLOB ${LIBNAME}_HEADERS *.hpp)
file(GLOB ${LIBNAME}_SOURCES *.cpp)

add_library(${LIBNAME} ${${LIBNAME}_HEADERS} ${${LIBNAME}_SOURCES})
set_target_properties(${LIBNAME} PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS ${LIBNAME} DESTINATION ${LIBNAME}/lib)
install(FILES ${${LIBNAME}_HEADERS} DESTINATION ${LIBNAME}/include)
