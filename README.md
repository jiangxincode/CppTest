# CppTest

[![Build and Release](https://github.com/jiangxincode/CppTest/actions/workflows/BuildAndRelease.yml/badge.svg)](https://github.com/jiangxincode/CppTest/actions/workflows/BuildAndRelease.yml)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/20284/badge.svg)](https://scan.coverity.com/projects/jiangxincode-cpptest)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=alert_status)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Doxygen Docs](https://codedocs.xyz/jiangxincode/CppTest.svg)](https://codedocs.xyz/jiangxincode/CppTest/)

## 整体架构

一些相互独立的C++/C小程序或者验证程序，通过CMake组织，大部分都可以同时运行在Windows/Linux/Mac平台。各个程序相互独立，方便拆解。

通过本项目你可以学习到如下内容：

* 如何通过cmake组织工程
* 如何使用vcpkg
* 如何利用Github Actions进行自动化CI构建和代码质量检查

## 如何构建

一、安装vcpkg: <https://learn.microsoft.com/zh-cn/vcpkg/get_started/get-started>。

注意配置环境变量`VCPKG_INSTALLATION_ROOT`为vcpkg的根目录，同时配置`PATH`环境变量

二、安装依赖, 参考: <ttps://github.com/jiangxincode/CppTest/actions/workflows/BuildAndRelease.yml>
    
Linux: 

```shell
sudo apt install build-essential autotools-dev libtool
sudo apt install -y libgtk-3-dev
sudo apt install libgl-dev libglu1-mesa-dev libx11-dev libxrandr-dev libxi-dev
```

MacOS:

```shell
brew libtool automake
brew install gtk+3 libffi
brew install xquartz libx11 libxi libxrandr libxxf86vm mesa
```

Windows

安装`Microsoft Virual C++`

三、构建, 参考: <ttps://github.com/jiangxincode/CppTest/actions/workflows/BuildAndRelease.yml>

```shell
cmake --preset ${{ matrix.preset }}
cmake --build --preset ${{ matrix.preset }}
ctest --preset ${{ matrix.preset }}
```

Linux: ["linux-x64-debug", "linux-x64-release"]
macos: ["macos-x64-debug", "macos-x64-release"]
windows: ["windows-x64-debug", "windows-x64-release", "windows-x64-mingw-debug", "windows-x64-mingw-release"]

## 文件说明

### src/OpenGL

通过Demo学习OpenGL+FreeGlut

![](https://raw.githubusercontent.com/jiangxincode/PicGo/master/20241024144017.png)

### src/OpenSSLTest

通过Demo学习OpenSSL中的加解密算法

### src/msvc/Elevator

一个基于C++和MFC的电梯调度演示程序

![](https://raw.githubusercontent.com/jiangxincode/PicGo/master/20240928113329.png)

### src/LCTest

Some exercises for C in Linux environment

### src/ImageViewer

An image viewer. 基于`GTK+`。

### src/SumCode

计算某个项目的代码行数

* Version 0.01: 完成基本结构，能够实现基本操作。
* Version 0.02: 实现目录更改功能，但还有一些bug待消除。
* Version 0.03: 实现特定文件类型的统计，优化了代码结构。

### src/CTest

main1xxy.c C语言程序设计, 2012 实验教材为《C语言程序设计教程学习指导》，xx代表章节，y代表该章节的习题序号

### src/SingleFileCpp

各个目录下都是单个C++文件，如：

* codevs: <http://codevs.cn>
* hwoj: 网上流传的一些华为OJ题目
* luogu: 洛谷: <https://www.luogu.org>
* nowcode: 牛客: <https://www.nowcoder.com/>
* openjudge: <http://openjudge.cn/>
* VerifyCppGrammar: 验证C++语法

### src/IdiomSolitaire

一个成语接龙小程序

### src/others

* 0000-1699:一些小程序
* 1700-1999:Data Structure
	* 第i章->main(17+i)
	* 部分常用数据结构总结到特定文件
* 2000-5000:一些小程序
	* main2565.cpp: swap data in array, but can not introduce new array

* 对于scanf的说明
	* 32位int 11位宽(-2147483648~+2147483647)
	* 32位unsigned 10位宽(0~4294967295)
	* float/double 20位宽
	* char *(%s) 根据实际内存容量设置

## Contributing

1. Fork it
2. Create your feature branch(`git check -b my-new-feature`)
3. Commit your changes(`git commit -am "Add some feature"`)
4. Push to the branch(`git push origin my-new-feature`)
5. Create new Pull Request

## License

+ The MIT License (MIT) http://mit-license.org/

