#ifndef __PHONEBOOKPROCESS_H__
#define __PHONEBOOKPROCESS_H__


/*
功能: 检查是否有两个或多个公司拥有相同的电话号码,并统计输出

输入参数: inFileName  - 包含个性电话号码个数与列表的源文件名      [格式请见题目说明PPT]
        outFileName - 输出统计重复号码的结果的目标文件名                  [格式请见题目说明PPT]

输出参数: 无
返回: 0 - 成功
        1 - 其它各种错误，如文件不存在
*/

int PhoneBookProcess(const char *inFileName,const char *outFileName);

#endif
