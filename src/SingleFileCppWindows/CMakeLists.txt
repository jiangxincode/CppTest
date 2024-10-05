IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_executable(FlappyBird
            FlappyBird.cpp)
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")