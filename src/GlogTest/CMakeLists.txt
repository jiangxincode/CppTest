find_package(glog CONFIG REQUIRED)

add_executable (GlogTest "GlogTest.cpp")

target_link_libraries(GlogTest PRIVATE glog::glog)

