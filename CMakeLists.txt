# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.20)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

SET(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project ("VCTest")

# 包含子项目。
add_subdirectory ("cmdplus")
add_subdirectory ("WindowTest")
add_subdirectory ("ConsoleTest")
add_subdirectory ("LeafCore")
add_subdirectory ("SimpleMFC")
add_subdirectory ("MFCTest")
add_subdirectory ("SchoolMIS")
add_subdirectory ("SimpleManageSystem")
add_subdirectory ("GlogTest")
add_subdirectory ("Books")
add_subdirectory ("OpenGL")
add_subdirectory ("OpenSSLTest")
add_subdirectory ("OJ")
add_subdirectory ("BlueToothExc")