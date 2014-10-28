# Test

jiangxinnju@163.com

http://github.com/jiangxincode

## 文件说明

* Test.cbp //codeblocks
* Test.depend //codeblocks
* Test.layout //codeblocks

* CppCheckResults.xml //cppcheck
* Test.cppcheck //cppcheck

* main.c主函数
* main.h主头文件

* 回收文件标记为//delete
* 0000:Test
* 0001-0499:ACM(000-499)
* 0500-1499:一些小程序
* 1500-1699:C++ Primer 15n0 for chapter n 16n0 for chapter 10+n
* 1700-1999:Data Structure
* 2000-2499:一些比较大的程序
* 2500-2599:程序设计基础，2014暑假

	* origin:111150034+蒋鑫+i_j now:main25ij
	* origin:111150034+蒋鑫+10 now:main2500
	* origin:111150034+蒋鑫+综合 now:main2501

* unsolved: 1620 1800 0520

* 对于scanf的说明
	* 32位int 11位宽(-2147483648~+2147483647)
	* 32位unsigned 10位宽(0~4294967295)
	* float/double 20位宽
	* char *(%s) 根据实际内存容量设置

* //delete:表示已删除可重用


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