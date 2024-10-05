# GTEST BEGIN
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# GTEST END

enable_testing()

add_executable(GTestMain
        GTestMain.cpp
        #[[main/binary_search_tree.cpp
        main/binary_search_tree.h
        main/binary_tree.cpp
        main/binary_tree.h
        test/test_binary_search_tree.cpp
        test/test_binary_tree.cpp]]
        main/factorial.cpp
        main/factorial.h
        #[[main/heap.cpp
        main/heap.h
        test/test_heap.cpp
        main/single_list.cpp]]
        main/LinkedSet.h
        main/miscellaneous.cpp
        main/miscellaneous.h
        main/sort.cpp
        main/sort.h
        main/string_process.cpp
        main/string_process.h
        main/circ_list.h
        main/contacts.cpp
        main/hash.hpp
        #[[main/josephus.cpp
        main/linear_list.h]]
        main/skip_list.h
        main/spherical_distance.cpp
        main/static_list.h
        #[[main/union_find_set.cpp
        main/union_find_set.h]]
        test/test_factorial.cpp
        test/test_linked_set.cpp
        test/test_miscellaneous.cpp
        test/test_sort.cpp
        test/test_string_process.cpp)

target_link_libraries(GTestMain
        GTest::gtest_main)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(GTestMain pthread)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

include(GoogleTest)
gtest_discover_tests(GTestMain)
