find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIRS})

add_executable(OpenGL OpenGL.cpp)

target_link_libraries(OpenGL ${GLUT_LIBRARIES})
