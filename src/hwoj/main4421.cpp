/**
 * 内存文件系统
 * 要求
 * 某产品需要实现一个内存文件系统，现在请你来实现目录与文件管理部分。
 * 	系统支持目录与文件。
 * 	目录可以包含其它目录与文件。
 * 	删除目录时，要求同时删除此目录包含的子目录和文件。
 * 	移动目录时，要求同时移动此目录包含的子目录和文件，并保证此目录下的子目录和文件层次结构不发生变化。
 * 	根目录为“root”，要求缺省存在，由考生程序自行实现。
 * 	除根目录（root），目录与文件有且仅有一个父目录。
 *
 * 图示
 *
 * 规格说明
 * 为了简化实现，假设：
 * 	目录名全局唯一，大小写敏感。
 * 	文件名全局唯一，大小写敏感。
 * 	目录名与文件名可以相同。
 * 	目录与文件的总个数没有限制。每个目录包含的目录以及文件个数没有限制。
 * 请实现如下接口
 * int CreateDir(const char * ParentDirName, const char * DirName)
 * 功能：在指定的目录（ParentDirName）下创建目录
 * 输入：
 * 	 ParentDirName 		父目录名
 * 	 DirName 			待创建的目录名
 * 返回：执行结果
 * 	成功返回0。
 * 	失败返回-1。如父目录（ ParentDirName）不存在，待创建的目录名（ DirName）已经存在，等等。
 *
 * 说明：
 * 1.	用例保证所有接口的输入指针不会为空，输入的字符串不会为空串。
 * 2.	所有接口中，调用者可能会释放字符串内存，需要考生自行保存内容。
 *
 * void DeleteDir(const char * DirName)
 * 功能：删除指定目录
 * 输入：
 * 	 DirName		待删除的目录名
 * 说明：
 * 1.	测试用例保证待删除的目录名（ DirName）不会为“root”。
 *
 * int MoveDir(const char * SrcDirName, const char * DestDirName)
 * 功能：把指定的目录（ SrcDirName ）移动到目标目录（ DestDirName）下
 * 输入：
 * 	 SrcDirName 		待移动的目录名
 * 	 DestDirName 		目标目录名
 * 返回：执行结果
 * 	成功返回0。
 * 	失败返回-1。如目录（ SrcDirName或DestDirName）不存在，目标目录是待移动目录本身，或其子目录、直接父目录，等等。
 * int CreateFile(const char * DirName, const char * FileName)
 * 功能：在指定目录（ DirName）下创建文件
 * 输入：
 * 	 DirName 			待创建文件所属的目录名
 * 	 FileName 			待创建的文件名
 * 返回：执行结果
 * 	成功返回0。
 * 	失败返回-1。如已有同名的文件存在，目录名（ DirName）不存在，等等。
 *
 * void DeleteFile(const char * FileName)
 * 功能：删除文件
 * 输入：
 * 	 FileName 		待删除的文件名
 *
 * unsigned int GetFileNum(const char * DirName)
 * 功能： 统计目录（ DirName）下的文件个数
 * 输入：
 * 	 DirName 		待统计的目录名
 * 返回：目录（ DirName）下的文件个数，包括子目录下的文件。
 * 说明：
 * 1.	目录（ DirName）不存在，返回0。
 *
 * void Clear(void)
 * 功能：清空所有数据，将系统恢复至初始化完成状态。
 */
#include <iostream>

int CreateDir(const char * ParentDirName, const char * DirName)
{
    return 0;
}

void DeleteDir(const char * DirName)
{
    return;
}

int MoveDir(const char * SrcDirName, const char * DestDirName)
{
    return 0;
}

int CreateFile(const char * DirName, const char * FileName)
{
    return 0;
}

void DeleteFile(const char * FileName)
{
    return;
}

unsigned int GetFileNum(const char * DirName)
{
    return 0;
}

void Clear(void)
{
    return;
}

int main()
{
    CreateDir("root", "DirA");
    CreateFile("DirA", "File1");
    std::cout << (1 == GetFileNum("DirA")) << std::endl;
    Clear();
}
