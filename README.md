# CppTest

[![Travis CI Build Status](https://travis-ci.org/jiangxincode/CppTest.svg?branch=master)](https://travis-ci.org/jiangxincode/CppTest)
[![Build status](https://ci.appveyor.com/api/projects/status/bmh3cjv2wchq5esl?svg=true)](https://ci.appveyor.com/project/jiangxincode/cpptest)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/20284/badge.svg)](https://scan.coverity.com/projects/jiangxincode-cpptest)
[![Doxygen Docs](https://codedocs.xyz/jiangxincode/CppTest.svg)](https://codedocs.xyz/jiangxincode/CppTest/)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=alert_status)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=bugs)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=code_smells)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=coverage)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=duplicated_lines_density)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=sqale_rating)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=reliability_rating)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Security Rating](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=security_rating)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Lines of Code](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=ncloc)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Technical Debt](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=sqale_index)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)
[![Vulnerabilities](https://sonarcloud.io/api/project_badges/measure?project=jiangxincode_CppTest&metric=vulnerabilities)](https://sonarcloud.io/dashboard?id=jiangxincode_CppTest)


jiangxinnju@163.com

http://github.com/jiangxincode

## 文件说明

* src/LCTest: Some exercises for C in Linux environment
* src/CTest:
    * main1xxy.c C语言程序设计, 2012 实验教材为《C语言程序设计教程学习指导》，xx代表章节，y代表该章节的习题序号
* src/codevs: <http://codevs.cn>
* src/hwoj: 网上流传的一些华为OJ题目
* src/others
    * 0000-1699:一些小程序
    * 1700-1999:Data Structure
    	* 第i章->main(17+i)
    	* 部分常用数据结构总结到特定文件
    * 2000-5000:一些小程序
        * main2565.cpp: swap data in array, but can not introduce new array
* test/ 单元测试文件

* 对于scanf的说明
	* 32位int 11位宽(-2147483648~+2147483647)
	* 32位unsigned 10位宽(0~4294967295)
	* float/double 20位宽
	* char *(%s) 根据实际内存容量设置

## 将要进行的改进

* //problem:表示存在问题
* //unsolved: 表示未解决问题
* //warning: 表示需要注意问题

* 继续使用cppcheck修复潜藏bug
* 完善公共类
* 利用doxygen产生的文档整理各种命名
* 逐步去除std带来的混乱
