find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# 包含 GLUT 头文件
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})

# 添加可执行文件
add_executable(OpenGL OpenGL.cpp)

# 链接 GLUT 库
target_link_libraries(OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
