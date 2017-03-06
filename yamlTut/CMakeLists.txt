cmake_minimum_required(VERSION 3.0)
project(YAML)

INCLUDE(${PROJECT_SOURCE_DIR}/FindYamlCpp05.cmake)


add_executable(YAML firstprog.cpp)
target_link_libraries(YAML yaml-cpp)
