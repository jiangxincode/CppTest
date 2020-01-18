cmake_minimum_required(VERSION 3.12)
project(CppTest CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
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

aux_source_directory(include/gtest gtest_h)
aux_source_directory(lib/gtest gtest_cpp)

add_executable(GTestMain
        ${gtest_h}
        ${gtest_cpp}
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

add_executable(CppTest
        src/main.cpp
        src/main.h
        src/test.cpp
        src/tools.cpp)

target_link_libraries(GTestMain pthread)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/nowcoder src/nowcoder/*.cpp)
foreach (source IN LISTS sources)
    string(REPLACE ".cpp" "" program ${source})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/nowcoder/${source})
    target_link_libraries(${program} m)
endforeach (source)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/MyFirstCCourse src/MyFirstCCourse/*.c)
foreach (source IN LISTS sources)
    string(REPLACE ".c" "" program ${source})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/MyFirstCCourse/${source})
    target_link_libraries(${program} m)
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