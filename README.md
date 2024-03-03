# CppTest

[![Build and Release](https://github.com/jiangxincode/CppTest/actions/workflows/BuildAndRelease.yml/badge.svg)](https://github.com/jiangxincode/CppTest/actions/workflows/BuildAndRelease.yml)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/20284/badge.svg)](https://scan.coverity.com/projects/jiangxincode-cpptest)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=alert_status)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Doxygen Docs](https://codedocs.xyz/jiangxincode/CppTest.svg)](https://codedocs.xyz/jiangxincode/CppTest/)

## 文件说明

### src/LCTest

Some exercises for C in Linux environment

### src/GTKPlus

Some exercises for GTK+ in Linux environment.

* MySqlDemo.c 来自于《GTK+2.0编程范例》 9
* gEmail.c 来自于《GTK+2.0编程范例》 10.1
* thread.c 来自于《GTK+2.0编程范例》 11.3 
* Local.c 来自于《GTK+2.0编程范例》 11.6
* 其它 《GTK+程序设计中文版》

### src/ImageViewer

An image viewer. 

来自于《GTK+ GNOME程序设计》第18章，由于GNOME库已经废弃，我迁移到了GTK: <https://bugs.launchpad.net/ubuntu/+source/libgnome/+bug/1771031>

### src/CTest

main1xxy.c C语言程序设计, 2012 实验教材为《C语言程序设计教程学习指导》，xx代表章节，y代表该章节的习题序号

### src/codevs

<http://codevs.cn>

### src/hwoj

网上流传的一些华为OJ题目

### src/IdiomSolitaire

A toy for idiom soliteaire. It is very instering.

#### Usage

+ -h: Show this help.
+ -i filename: Set the dictionary file. This program only support the GBK encoding dictionary!
+ -l: Be able to loop.
+ -e: Show every item when you strike the key, and 'e' to quit", stdout
+ -c: Set the initiate character.
+ -n num: Set the maximum idiom item number when output. Of course if there are not so many, It only show the exist.

#### TODO

+ add some extra features.

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

* main.c主函数
* main.h主头文件

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

## 版本改动

### Version 1.01

通过CppCheck检查，修复以下问题：

* The scope of the variable 'xxx' can be reduced.
* Variable 'term' is reassigned a value before the old one has been used.
* scanf without field width limits can crash with huge input data on some versions of libc.
* Obsolete function 'gets' called. It is recommended to use the function 'fgets' instead.
* Redundant code: Found a statement that begins with numeric constant.
* %d in format string (no. 1) requires 'int' but the argument type is 'unsigned int'.
* Array 'm[10]' accessed at index 10, which is out of bounds.

### Version 1.02

* 将所有文件设置为UTF-8编码，设置codeblocks默认编码为UTF-8,便于生成doxyblocks生成文档。

### Version 1.03

* 接受部分从Test工程中移入的文件

### Version 1.04

* 去除大部分非必须全局变量

### Version 1.05

* scanf without field width limits can crash with huge input data on some versions of libc.
* 接受部分从Test工程中移入的文件
* The scope of the variable 'count' can be reduced.
* Obsolete function 'gets' called. It is recommended to use the function 'fgets' instead.

### Version 1.06

* 修改doxygen设置，屏蔽部分测试函数

### Version 1.07

* 使用GLib重构部分代码。

### Version 1.08

* 整理文件

### Version 1.09

* 添加了部分文件
* 将所有源码改至src文件夹，方便source insight的使用
* 去除所有cppcheck检查警告
* 整理了README.md和.gitignore文件

### Version 1.10

* 规划了程序结构

### Version 1.11

* 将github上的mycode项目中的一部分纯C代码移入该项目

## Contributing

1. Fork it
2. Create your feature branch(`git check -b my-new-feature`)
3. Commit your changes(`git commit -am "Add some feature"`)
4. Push to the branch(`git push origin my-new-feature`)
5. Create new Pull Request

## License

+ The MIT License (MIT) http://mit-license.org/

