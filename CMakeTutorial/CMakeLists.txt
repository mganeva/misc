cmake_minimum_required(VERSION 3.0)
project(Tutorial)

set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)



set(FUNC_SRCS tutorial.cpp myfunc.h myfunc.cpp)

add_executable(Tutorial ${FUNC_SRCS})
target_link_libraries(Tutorial ${EXTRA_LIBS})

#include (CheckFunctionExists.cmake)




install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

#include (CheckFunctionExists.cmake)
#check_function_exists (log HAVE_LOG)
#check_function_exists (exp HAVE_EXP)
configure_file(
    "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
    "${PROJECT_BINARY_DIR}/TutorialConfig.h")

include_directories("${PROJECT_BINARY_DIR}")

message("Project binary dir is: ${PROJECT_BINARY_DIR}")

#include_directories("${PROJECT_SOURCE_DIR}/MathFunctions")

#add_subdirectory(MathFunctions)

#target_link_libraries(Tutorial MathFunctions)

option(USE_MYMATH
    "Use tutorial provided math implementation" ON)

if(USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/MathFunctions")
    add_subdirectory(MathFunctions)
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MYMATH)





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
