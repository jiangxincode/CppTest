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

add_executable(nowcoder0002
        src/nowcoder/nowcoder0002.cpp)

add_executable(nowcoder0003
        src/nowcoder/nowcoder0003.cpp)

add_executable(nowcoder0004
        src/nowcoder/nowcoder0004.cpp)

add_executable(nowcoder0005
        src/nowcoder/nowcoder0005.cpp)

add_executable(nowcoder0006
        src/nowcoder/nowcoder0006.cpp)

add_executable(nowcoder0007
        src/nowcoder/nowcoder0007.cpp)

#[[add_executable(nowcoder0008
        src/nowcoder/nowcoder0008.cpp)]]

#[[add_executable(nowcoder0009
        src/nowcoder/nowcoder0009.cpp)]]

add_executable(nowcoder0010
        src/nowcoder/nowcoder0010.cpp)

add_executable(nowcoder0011
        src/nowcoder/nowcoder0011.cpp)

add_executable(nowcoder0012
        src/nowcoder/nowcoder0012.cpp)

add_executable(nowcoder0013
        src/nowcoder/nowcoder0013.cpp)

add_executable(nowcoder0014
        src/nowcoder/nowcoder0014.cpp)

add_executable(nowcoder0015
        src/nowcoder/nowcoder0015.cpp)

add_executable(nowcoder0016
        src/nowcoder/nowcoder0016.cpp)

add_executable(nowcoder0017
        src/nowcoder/nowcoder0017.cpp)

add_executable(nowcoder0018
        src/nowcoder/nowcoder0018.cpp)

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


file(GLOB APP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/src/MyFirstCCourse src/MyFirstCCourse/*.c)

MESSAGE( STATUS "${APP_SOURCES}")

foreach (sourcefile IN LISTS APP_SOURCES)
    string(REPLACE ".c" "" program ${sourcefile})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/MyFirstCCourse/${sourcefile})
endforeach (sourcefile)