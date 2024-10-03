# CppTest

[![Build and Release](https://github.com/jiangxincode/CppTest/actions/workflows/BuildAndRelease.yml/badge.svg)](https://github.com/jiangxincode/CppTest/actions/workflows/BuildAndRelease.yml)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/20284/badge.svg)](https://scan.coverity.com/projects/jiangxincode-cpptest)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=alert_status)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Doxygen Docs](https://codedocs.xyz/jiangxincode/CppTest.svg)](https://codedocs.xyz/jiangxincode/CppTest/)

## 文件说明

### src/LCTest

Some exercises for C in Linux environment

### src/ImageViewer

An image viewer. 基于`GTK+`。

### src/CTest

main1xxy.c C语言程序设计, 2012 实验教材为《C语言程序设计教程学习指导》，xx代表章节，y代表该章节的习题序号

### src/SingleFileCpp

各个目录下都是单个C++文件，如：

* codevs: <http://codevs.cn>
* hwoj: 网上流传的一些华为OJ题目
<<<<<<< HEAD
* luogu: 洛谷: <https://www.luogu.org>
* nowcode: 牛客: <https://www.nowcoder.com/>
* openjudge: <http://openjudge.cn/>
=======
* luogu
* nowcode
* openjudge
>>>>>>> 26e8ae75e3cb06ca6a9c96a7442dd3e37a83640f
* VerifyCppGrammar: 验证C++语法

### src/IdiomSolitaire

A toy for idiom solitaire.

### src/others

* 0000-1699:一些小程序
* 1700-1999:Data Structure
	* 第i章->main(17+i)
	* 部分常用数据结构总结到特定文件
* 2000-5000:一些小程序
	* main2565.cpp: swap data in array, but can not introduce new array

### test

单元测试文件

### data

测试输入文件以及其他需要长期存储的文件

### CLAH

C语言算法速查手册

### CLCDC

C语言课程设计案例精编

### 其它

* jiangxin.c常用自定义函数
* jiangxin.h常用自定义函数的声明

* 对于scanf的说明
	* 32位int 11位宽(-2147483648~+2147483647)
	* 32位unsigned 10位宽(0~4294967295)
	* float/double 20位宽
	* char *(%s) 根据实际内存容量设置

## 将要进行的改进

C++ 
* //problem:表示存在问题
* //unsolved: 表示未解决问题
* //warning: 表示需要注意问题

* 继续使用cppcheck修复潜藏bug
* 完善公共类
* 利用doxygen产生的文档整理各种命名
* 逐步去除std带来的混乱

C
* 增加注释
* 规范化代码结构
* 综合链表问题
* 综合主要数据结构
* 合并常用函数
* 减少全局变量和宏定义数量
* 各种检测工具check

## Contributing

1. Fork it
2. Create your feature branch(`git check -b my-new-feature`)
3. Commit your changes(`git commit -am "Add some feature"`)
4. Push to the branch(`git push origin my-new-feature`)
5. Create new Pull Request

## License

+ The MIT License (MIT) http://mit-license.org/

