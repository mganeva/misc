cmake_minimum_required(VERSION 3.0)
project(Tutorial)

set(FUNC_SRCS tutorial.cpp myfunc.h myfunc.cpp)

add_executable(Tutorial ${FUNC_SRCS})
