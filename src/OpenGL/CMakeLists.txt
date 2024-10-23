find_package(OpenGL REQUIRED)
find_package(FreeGLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

add_executable(OpenGL OpenGL.cpp)

target_link_libraries(OpenGL
        PRIVATE
        ${OPENGL_LIBRARIES}
        $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>
)
