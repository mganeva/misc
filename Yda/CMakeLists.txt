cmake_minimum_required(VERSION 3.0)
project(YDASave)

set(SaveYda_VERSION_MAJOR 1)
set(SaveYda_VERSION_MINOR 0)

INCLUDE(FindYamlCpp05.cmake)

configure_file(
    "${PROJECT_SOURCE_DIR}/YdaConfig.h.in"
    "${PROJECT_BINARY_DIR}/YdaConfig.h")

set(CLASS_SRCS SaveYda.cpp SaveYda.h main.cpp)

add_executable(YDASave ${CLASS_SRCS})
target_link_libraries(YDASave yaml-cpp)

install(TARGETS YDASave DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)
