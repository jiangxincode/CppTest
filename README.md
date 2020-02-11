# VCTest

[![Build status](https://ci.appveyor.com/api/projects/status/6hoc2mfahogm1gt2?svg=true)](https://ci.appveyor.com/project/jiangxincode/vctest)

安装vcpgk：

vcpkg: <https://github.com/Microsoft/vcpkg/>

安装依赖包：

.\vcpkg.exe install openssl-windows
.\vcpkg.exe install freeglut
.\vcpkg.exe install glog

MemeryLeakCheck.cpp 检测内存泄露的方法，必须在VS中编译运行。