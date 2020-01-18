cmake_minimum_required(VERSION 3.12)
project(CppTest CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(CMAKE_BUILD_TYPE "Debug")

include_directories(include)

add_executable(luoguP1876
        src/luogu/luoguP1876.cpp)

add_executable(openjudge_zz_3
        src/openjudge/openjudge_zz_3.cpp)

add_executable(main2564
        src/others/main2564.cpp)

add_executable(main2565
        src/others/main2565.cpp)

add_executable(main2545
        src/others/main2545.cpp)

add_executable(main2544
        src/others/main2544.cpp)

add_executable(main2567
        src/others/main2567.cpp)

add_executable(CppTest
        src/main.cpp
        src/main.h
        src/test.cpp
        src/tools.cpp)

add_executable(SumCode
        src/SumCode/main.cpp
        src/SumCode/libjiangxin.cpp
        src/SumCode/function.cpp
        src/SumCode/function.h
        src/SumCode/jiangxin.h)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/nowcoder src/nowcoder/*.cpp)
foreach (source IN LISTS sources)
    string(REPLACE ".cpp" "" program ${source})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/nowcoder/${source})
    IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        target_link_libraries(${program} m)
    ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
endforeach (source)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/MyFirstCCourse src/MyFirstCCourse/*.c)
foreach (source IN LISTS sources)
    string(REPLACE ".c" "" program ${source})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/MyFirstCCourse/${source})
    IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        target_link_libraries(${program} m)
    ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
endforeach (source)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/LCTest src/LCTest/*.c)
    foreach (source IN LISTS sources)
        string(REPLACE ".c" "" program ${source})
        add_executable(${program} ${CMAKE_SOURCE_DIR}/src/LCTest/${source})
        target_link_libraries(${program} m)
    endforeach (source)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_executable(FlappyBird
            src/FlappyBird.cpp)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    MESSAGE(STATUS "current platform: FreeBSD")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

# GTEST BEGIN
set(DCMAKE_SH="CMAKE_SH-NOTFOUND")
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
# GTEST END

add_executable(GTestMain
        src/GTestMain.cpp
        #[[src/common/binary_search_tree.cpp
        src/common/binary_search_tree.h
        src/common/binary_tree.cpp
        src/common/binary_tree.h
        test/common/test_binary_search_tree.cpp
        test/common/test_binary_tree.cpp]]
        src/common/factorial.cpp
        src/common/factorial.h
        #[[src/common/heap.cpp
        src/common/heap.h
        test/common/test_heap.cpp
        src/common/single_list.cpp]]
        src/common/LinkedSet.h
        src/common/miscellaneous.cpp
        src/common/miscellaneous.h
        src/common/sort.cpp
        src/common/sort.h
        src/common/string_process.cpp
        src/common/string_process.h
        src/common/circ_list.h
        src/common/contacts.cpp
        src/common/hash.hpp
        src/common/input.cpp
        #[[src/common/josephus.cpp
        src/common/linear_list.h]]
        src/common/skip_list.h
        src/common/spherical_distance.cpp
        src/common/static_list.h
        #[[src/common/union_find_set.cpp
        src/common/union_find_set.h]]
        test/common/test_factorial.cpp
        test/common/test_linked_set.cpp
        test/common/test_miscellaneous.cpp
        test/common/test_sort.cpp
        test/common/test_string_process.cpp)

target_link_libraries(GTestMain
        gtest_main)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(GTestMain pthread)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")