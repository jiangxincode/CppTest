cmake_minimum_required(VERSION 3.14)
project(CppTest CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

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

add_executable(IdiomSolitaire
        src/IdiomSolitaire/main.c
        src/IdiomSolitaire/tailor.h
        src/IdiomSolitaire/getopt.h
        src/IdiomSolitaire/getopt.c)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/codevs src/codevs/*.cpp)
foreach (source IN LISTS sources)
    string(REPLACE ".cpp" "" program ${source})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/codevs/${source})
endforeach (source)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/hwoj src/hwoj/*.cpp)
foreach (source IN LISTS sources)
    string(REPLACE ".cpp" "" program ${source})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/hwoj/${source})
endforeach (source)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/others src/others/*.cpp)
foreach (source IN LISTS sources)
    string(REPLACE ".cpp" "" program ${source})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/others/${source})
endforeach (source)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/nowcoder src/nowcoder/*.cpp)
foreach (source IN LISTS sources)
    string(REPLACE ".cpp" "" program ${source})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/nowcoder/${source})
    IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        target_link_libraries(${program} m)
    ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
endforeach (source)

file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/CTest src/CTest/*.c)
foreach (source IN LISTS sources)
    string(REPLACE ".c" "" program ${source})
    add_executable(${program} ${CMAKE_SOURCE_DIR}/src/CTest/${source})
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

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)
    file(GLOB sources RELATIVE ${CMAKE_SOURCE_DIR}/src/GTKPlus src/GTKPlus/*.c)
    foreach (source IN LISTS sources)
        string(REPLACE ".c" "" program ${source})
        add_executable(${program} ${CMAKE_SOURCE_DIR}/src/GTKPlus/${source})
        target_link_libraries(${program} PkgConfig::GTK3)
    endforeach (source)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GNOME IMPORTED_TARGET libgnome-2.0 libgnomeui-2.0)
    if (GNOME_FOUND)
        add_executable(ImageViewer
                src/ImageViewer/main.c
                src/ImageViewer/fileselect.c
                src/ImageViewer/fileselect.h
                src/ImageViewer/imageviewerutility.c
                src/ImageViewer/imageviewerutility.h
                src/ImageViewer/ImageWindow.c
                src/ImageViewer/ImageWindow.h
                src/ImageViewer/mainwindow.c
                src/ImageViewer/mainwindow.h
                src/ImageViewer/mainwindowhandlers.h)
        target_link_libraries(ImageViewer PkgConfig::GNOME)
    endif ()
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_executable(FlappyBird
            src/FlappyBird.cpp)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    MESSAGE(STATUS "current platform: FreeBSD")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

# GTEST BEGIN
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# GTEST END

enable_testing()

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
        GTest::gtest_main)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(GTestMain pthread)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

include(GoogleTest)
gtest_discover_tests(GTestMain)
