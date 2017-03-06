cmake_minimum_required(VERSION 3.0)
project(Tutorial)

set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)

set(CMAKE_REQUIRED_INCLUDES math.h)
set(CMAKE_REQUIRED_LIBRARIES m)

include(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)

message("CMake_Root is:${CMAKE_ROOT}")

option(USE_MYMATH
    "Use tutorial provided math implementation" ON)

configure_file(
    "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
    "${PROJECT_BINARY_DIR}/TutorialConfig.h")

include_directories("${PROJECT_BINARY_DIR}")

if(USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/MathFunctions")
    add_subdirectory(MathFunctions)
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MYMATH)

set(FUNC_SRCS tutorial.cpp myfunc.h myfunc.cpp)

add_executable(Tutorial ${FUNC_SRCS})
target_link_libraries(Tutorial ${EXTRA_LIBS})

install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

message("Project binary dir is: ${PROJECT_BINARY_DIR}")


enable_testing()

macro (do_test arg result)
add_test(TutorialComp${arg} Tutorial ${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)

add_test(TutorialRuns Tutorial 25)


do_test (1 "1 is 1")
do_test (0.001 "0.01 is 0.2231301601484298")


do_test (25 "25 is 5")
do_test (-25 "-25 is -nan")
do_test (0.0001 "0.0001 is 0.01")

add_test(TutorialComp25 Tutorial 25)
set_tests_properties(TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

add_test(TutorialNegative Tutorial -25)
set_tests_properties(TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")

add_test(TutorialSmall Tutorial 0.0001)
set_tests_properties(TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")

add_test(TutorialUsage Tutorial)
set_tests_properties(TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

include(InstallRequiredSystemLibraries)
set(CPACK_RESURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSOIN_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)

include(CTest)
set(CTEST_PROJECT_NAME "Tutorial")
