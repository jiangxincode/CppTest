# ExerciseC

jiangxinnju@163.com

http://github.com/jiangxincode

## 文件说明

* ExerciseC.cbp //codeblocks
* ExerciseC.depend //codeblocks
* ExerciseC.layout //codeblocks

* main.c主函数
* main.h主头文件

* jiangxin.c常用自定义函数
* jiangxin.h常用自定义函数的声明

* 0000-0999:平时练习题
* 1000-1199:C语言程序设计, 2012 实验教材为《C语言程序设计教程学习指导》
	* origin:7-4.c now:main1074
	* origin:12-5.c now:main1125
* //delete:表示已删除可重用

* CppCheckResults.xml //cppcheck
* ExerciseC.cppcheck //cppcheck


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