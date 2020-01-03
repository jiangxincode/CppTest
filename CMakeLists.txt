cmake_minimum_required(VERSION 3.12)
project(CppTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/gtest)
include_directories(include/gtest/internal)
include_directories(single_file_src)
include_directories(src)
include_directories(src/gtest)
include_directories(test)

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

add_executable(main2564
        src/single_file_src/main2564.cpp)

add_executable(main2565
        src/single_file_src/main2565.cpp)

add_executable(main2545
        src/single_file_src/main2545.cpp)

add_executable(main2544
        src/single_file_src/main2544.cpp)

add_executable(CppTest
        include/gtest/internal/gtest-death-test-internal.h
        include/gtest/internal/gtest-filepath.h
        include/gtest/internal/gtest-internal.h
        include/gtest/internal/gtest-linked_ptr.h
        include/gtest/internal/gtest-param-util-generated.h
        include/gtest/internal/gtest-param-util.h
        include/gtest/internal/gtest-port.h
        include/gtest/internal/gtest-string.h
        include/gtest/internal/gtest-tuple.h
        include/gtest/internal/gtest-type-util.h
        include/gtest/gtest-death-test.h
        include/gtest/gtest-message.h
        include/gtest/gtest-param-test.h
        include/gtest/gtest-printers.h
        include/gtest/gtest-spi.h
        include/gtest/gtest-test-part.h
        include/gtest/gtest-typed-test.h
        include/gtest/gtest.h
        include/gtest/gtest_pred_impl.h
        include/gtest/gtest_prod.h
        lib/gtest/gtest-death-test.cc
        lib/gtest/gtest-filepath.cc
        lib/gtest/gtest-internal-inl.h
        lib/gtest/gtest-port.cc
        lib/gtest/gtest-printers.cc
        lib/gtest/gtest-test-part.cc
        lib/gtest/gtest-typed-test.cc
        lib/gtest/gtest.cc
        src/binary_search_tree.cpp
        src/binary_search_tree.h
        src/binary_tree.cpp
        src/binary_tree.h
        src/circ_list.h
        src/contacts.cpp
        src/factorial.cpp
        src/factorial.h
        src/hash.hpp
        src/heap.cpp
        src/heap.h
        src/input.cpp
        src/josephus.cpp
        src/linear_list.h
        src/LinkedSet.h
        src/main.cpp
        src/main.h
        src/test.cpp
        src/miscellaneous.cpp
        src/miscellaneous.h
        src/single_list.cpp
        src/skip_list.h
        src/sort.cpp
        src/sort.h
        src/spherical_distance.cpp
        src/static_list.h
        src/string_process.cpp
        src/string_process.h
        src/union_find_set.cpp
        src/union_find_set.h
        test/test_binary_search_tree.cpp
        test/test_binary_tree.cpp
        test/test_factorial.cpp
        test/test_heap.cpp
        test/test_linked_set.cpp
        test/test_miscellaneous.cpp
        test/test_sort.cpp
        test/test_string_process.cpp)

target_link_libraries(CppTest pthread)