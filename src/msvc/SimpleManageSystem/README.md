# SimpleManageSystem

## 项目列表

* HospitalSys
* LibraySystemC
* ShoppingSys
* ShopSysC1

 VS2017无法使用VC6.0的lib，所以删除了依赖库，添加了空实现，仅保证编译通过

* LoanSys
* SubwayChargeC0

## HospitalSys日志

### Version 0.01

* 基本完成，通过了所有给出的单元测试

## ShoppingSys日志

### Version 0.01

* 基本完成，通过了所有给出的单元测试

## ShopSysC1日志

### Version 0.01

* 基本完成框架设计
* 统一信息输出

### 待处理问题

* index和recordNum看看能不能合并
* lastTime插入时没有更新
* 罚款逻辑错误
* 未通过测试用例

## 贷款申请系统日志

### Version 0.01

* 初始化环境

### Version 0.02

* 完成基本框架

### Version 0.03

* 基本完成所有功能，对于时间的更新还有一些bugs需要修复

## 地铁管理系统日志

### Version 0.01

* 初始化环境

### Version 0.02

* 基本完成框架结构

### Version 0.03

* 重新设计了一些函数结构，优化了框架结构
* 基本完成除写文件以外的所有操作

### Version 0.04

* 修改了RemoveNodeByCardNo函数
* 删除了部分错误信息重复输出
* 完成了注销功能，通过了所有测试用例

### Version 0.05

* 修改了opQueryHistoryChargeListProc函数，实现了写文件功能

### Version 0.06

* 优化了程序结构，合并了部分文件

### Version 0.07

* 规范了信息输出
* 将临时输出文件输出到temp文件夹

### 待处理问题

* 对日志数量和链表最大长度问题进行检查
* 通过PC-Lint静态代码检查（回来完成，效率更高）