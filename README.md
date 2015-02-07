# ExerciseC

jiangxinnju@163.com

http://github.com/jiangxincode

## 文件说明

* ExerciseC.cbp //codeblocks
* ExerciseC.depend //codeblocks
* ExerciseC.layout //codeblocks

* bin/ //可运行二进制文件 不同步
* obj/ //中间obj文件 不同步

* .ccc/ //Cccc(C and C++ Code Counter)产生的关于代码信息的相关文件 不同步

* .git/ //git
* .gitattributes //git
* .gitignore //git

* CppCheckResults.xml //cppcheck 不同步
* ExerciseC.cppcheck //cppcheck 不同步

* include/ //glib所用的头文件glib-dev_2.28.8-1_win32 不同步
* lib/ //glib所使用的库文件glib-dev_2.28.8-1_win32 不同步

* temp/ //临时输出文件所在的文件夹 不同步
* data/ //测试输入文件以及其他需要长期存储的文件

* SI_PROJECT/ //SourceInsight文件夹 不同步

* src/ //所有源文件所在文件夹

* main.c主函数
* main.h主头文件

* jiangxin.c常用自定义函数
* jiangxin.h常用自定义函数的声明

* 0000-0999:平时练习题
* 1000-1199:C语言程序设计, 2012 实验教材为《C语言程序设计教程学习指导》
	* origin:7-4.c now:main1074
	* origin:12-5.c now:main1125

* //delete:表示已删除可重用

## 待修复问题

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

