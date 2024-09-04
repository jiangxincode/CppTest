enable_language(RC)

aux_source_directory(. DIR_SRCS)
add_executable (WindowTest WIN32 "WindowTest.cpp" "WindowTest.h" "WindowTest.ico" "WindowTest.rc" "Resource.h" "small.ico")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WindowTest PROPERTY CXX_STANDARD 20)
endif()
