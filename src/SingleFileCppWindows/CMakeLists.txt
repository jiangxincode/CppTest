IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_executable(FlappyBird
            FlappyBird.cpp)
    target_compile_options(FlappyBird
        PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
    )
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")