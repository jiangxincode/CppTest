# 添加可执行文件
add_executable(LibTest test.cpp)

# 链接到 MyLib 库
target_link_libraries(LibTest PRIVATE libjiangxin)
