# CppTest

jiangxinnju@163.com

http://github.com/jiangxincode

## 文件说明

* //problem:表示存在问题
* //unsolved: 表示未解决问题
* //warning: 表示需要注意问题


* test/ 单元测试文件
* src/ 源代码文件
    * gtest/
    * main.c主函数
    * main.h主头文件
    * ...
* include/ 第三方依赖库头文件


* 0000-1699:一些小程序
* 2000-3000:一些小程序
    * main2565.cpp: swap data in array, but can not introduce new array

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
