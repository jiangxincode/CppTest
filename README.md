# CppTest

jiangxinnju@163.com

http://github.com/jiangxincode

## 文件说明

* //problem:表示存在问题
* //unsolved: 表示未解决问题
* //warning: 表示需要注意问题


* test/ 单元测试文件
* src/ 源代码文件
    * codevs/ OJ
    * openjudge/ OJ
    * gtest/
    * main.c主函数
    * main.h主头文件
    * ...
* include/ 第三方依赖库头文件


* 0500-1699:一些小程序
* 2000-3000:一些小程序

* 1700-1999:Data Structure

	* 第i章->main(17+i)
	* 部分常用数据结构总结到特定文件


* 对于scanf的说明
	* 32位int 11位宽(-2147483648~+2147483647)
	* 32位unsigned 10位宽(0~4294967295)
	* float/double 20位宽
	* char *(%s) 根据实际内存容量设置

## 将要进行的改进

* 继续使用cppcheck修复潜藏bug
* 完善公共类
* 利用doxygen产生的文档整理各种命名
* 逐步去除std带来的混乱

## 版本改动

### Version 1.01

通过CppCheck检查，修复以下问题：

* Uninitialized variable: sum
* Possible null pointer dereference: us
* Memory leak: maxArr
* Variable 'ch' is reassigned a value before the old one has been used.
* Variable 'int_set' is assigned in constructor body. Consider performing initialization in initialization list.
* Function parameter 'query' should be passed by reference.
* scanf without field width limits can crash with huge input data.

### Version 1.02

* 去除所有.h文件中的using namespace std;

### Version 1.03

* 将所有文件设置为UTF-8编码，设置codeblocks默认编码为UTF-8,便于生成doxyblocks生成文档。

### Version 1.04

* 设置工程logo，用于完善文档
* 删除main2572
* 部分文件重新用C++格式代替C格式
* 部分文件移入ExerciseC

通过CppCheck检查，修复以下问题：

* scanf without field width limits can crash with huge input data.
* The scope of the variable 'flag' can be reduced.
* Unused variable: result
* Variable 'ch' is assigned a value that is never used.
* Member variable 'LinkNode<int>::data' is not initialized in the constructor.

### Version 1.05

通过CppCheck检查，修复以下问题：

* Member variable 'binary_node::parent' is not initialized in the constructor.
* Obsolete function 'gets' called. It is recommended to use the function 'fgets' instead.
* Storing getchar() return value in char variable and then comparing with EOF.

### Version 1.06

* 增加部分注释
* struct or union member 'test::i_var' is never used
* 去除了全部宏变量，使用局部const常量或者全局static const常量（限制在本文件中）代替
* 修复hash类

### Version 1.07

* 去除所有cstdio/stdio.h
* 去除部分cstdlib/stdlib.h

### Version 1.08

* 去除所有printf/scanf
* 部分文件移入ExerciseC

### Version 1.09

* 将排序函数单独列出
* 把有关堆和树的部分列出

### Version 1.10

* 练习华为OJ
* 修改之前的部分代码

### Version 1.11

* 练习华为OJ
* 修改之前的部分代码

### Version 1.12

* 去除部分cppcheck检查选项
* 将所有代码移至src文件夹

### Version 1.13

* 去除所有华为OJ题
* 修改了本README

### Version 1.14

* 加入gtest测试框架


### Version 1.15

* 完成对sort.cpp的单元测试

### Version 1.16

* 完成heap.cpp的单元测试

### Version 1.17

* 完成binary_tree.cpp/binary_search_tree.cpp的单元测试

### Version 1.18

### Version 2.00

* 更新了README.md
* 将codevs的题目移到单独的文件夹
* 整理了其它无用代码
