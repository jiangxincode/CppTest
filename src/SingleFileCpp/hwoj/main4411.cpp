/**
 * 迷你sql引擎
 * 实现一个小型sql解析执行引擎
 * 1.设计规则
 *     1、支持的数据类型：
 *      integer : 整型，有符号 4 字节整数；
 *      text : 变长字符串；（实现的时候，内部可以直接用char*）
 *     2、支持语法：
 *      SQL关键字(包括数据类型)不区分大小写，表名/列名/列值 区分大小写；
 *         SQL关键字包括：
 *       CREATE TABLE/INTEGER/TEXT/DROP TABLE/INSERT INTO/VALUES/ORDER BY/
 *       SELECT FROM WHERE/ORDER BY/DELETE FROM WHERE
 *       SQL语句中的特殊字符包括：( ) ' ; =
 *     3、语法细节：
 *      关于语句返回的错误信息，请参考.h文件定义
 *      创建表：CREATE TABLE table_name (col1_name   integer,col2_name   text);最大列数为5,列号    从1开始
 *      删除表：DROP TABLE table_name;
 *      插入记录：INSERT INTO table_name VALUES (100, 'Bananas');允许有重复
 *      查询记录：SELECT * FROM table_name WHERE col1_name = 100;
 *          SELECT * FROM table_name WHERE col2_name = 'Bananas' ORDER BY col1_name;
 *         1、ORDER BY 以升序排列
 *         2、当前SELECT关键字后，仅支持*（即返回所有列，列顺序按照创建表时候的列顺序），不需要考虑返回局部列的情况
 * 2.SQL语句执行接口
 *
 *      输入: const char *sql ：  SQL语句
 *
 *      输出:   无输出
 *
 *      返回: SQL语句执行后的结果集，只有SELECT语句返回的结果集可能存在多于1条的情况
 *        CREATE TABLE/DROP TABLE/INSERT INTO 语句返回的结果集只有一条记录，
 *        反映出当前语句的执行结果 。
 *        如CREATE TABLE执行成功后返回CREATE TABLE SUCCESS，失败则返回CREATE TABLE FAILED
 * 3.SQL语句执行接口
 *      功能:从上面 sql_execute 接口已经说明，结果集只有两种类情况：
 *    (1) CREATE TABLE/DROP TABLE/INSERT INTO 语句返回的结果集只有一条记录，
 *    使用方式如下：
 *    RecordSet rs =
 *    sql_execute("CREATE TABLE table_select_multi ( id integer, name text );");
 *    Record rcd = get_record(rs, 0);
 *    char * rcd_s = record_to_string(rcd);
 *    int ret = strcmp(rcd_s, "CREATE TABLE SUCCESS");
 *    (2) SELECT语句返回的结果集可能存在多于1条的情况，使用方式：
 *    RecordSet rs = sql_execute("SELECT * FROM table_select_multi ORDER BY id;");
 *    // 取第一行
 *    Record rcd = get_record(rs, 0);
 *    char * rcd_s = record_to_string(rcd);
 *    ret = strcmp(rcd_s, "100, 'Bananas'");
 *    CPPUNIT_ASSERT(ret == 0);
 *    // 取第二行
 *    rcd = get_record(rs, 1);
 *    rcd_s = record_to_string(rcd);
 *    ret = strcmp(rcd_s, "200, 'Apple'");
 *    CPPUNIT_ASSERT(ret == 0);
 *
 *      输入: const RecordSet rs ：  结果集
 *    int index ：           行号（行号从0开始）
 *
 *      输出:   无输出
 *
 *      返回: 结果集rs中的第index条记录
 * 其他功能及特性详见工程
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "iostream"

/////////////////////////////////// 宏定义 ////////////////////////////////////
//typedef char boolean;
#define true  (1)
#define false (0)
typedef int Oid;

/// 函数功能尚未实现
#define FAILED  (-1)
#define SUCCESS (0)

/// 表名最大字符数
#define TABLE_NAME_LEN (32)

/// 记录内容最大长度
#define RECORD_CONTENT_MAX_LEN (20)

/// 表中列数最大值
#define TABLE_MAX_COL (5)

///////////////////////////////// 总体要求 ////////////////////////////////////
/// 1. SQL关键字(包括数据类型)不区分大小写，表名/列名/列值 区分大小写；
/// 2. SQL关键字包括：
///    CREATE TABLE/INTEGER/TEXT/DROP TABLE/INSERT INTO/VALUES/ORDER BY/
///    SELECT FROM WHERE/ORDER BY/DELETE FROM WHERE
/// 3. SQL语句中的特殊字符包括：( ) ' ; =




///////////////////////////////// 结构定义 ////////////////////////////////////
/// 查询结果记录
struct db_record
{
    int error;
    char result[1024];
};
typedef struct db_record *Record;

/// 查询结果记录集
struct db_record_set
{
    char result[1024];
    struct db_record_set *next;
};
typedef struct db_record_set *RecordSet;


//////////////////////////////// 引擎接口定义 /////////////////////////////////

/******************************************************************************
 * @Description : SQL语句执行接口
 *
 * @param sql : [IN] 需要执行的SQL语句
 *
 * @return : SQL语句执行后的结果集，只有SELECT语句返回的结果集可能存在多于1条的情况
 *           CREATE TABLE/DROP TABLE/INSERT INTO 语句返回的结果集只有一条记录，
 *           反映出当前语句的执行结果
******************************************************************************/
RecordSet sql_execute(const char *sql);


//////////////////////////////// 记录集接口定义 ///////////////////////////////

/******************************************************************************
 * @Description : 从结果集中获取第index条记录
 *     从上面 sql_execute 接口已经说明，结果集只有两种类情况：
 *     (1) CREATE TABLE/DROP TABLE/INSERT INTO 语句返回的结果集只有一条记录，
 *     使用方式如下：
 *     RecordSet rs =
 *     sql_execute("CREATE TABLE table_select_multi ( id integer, name text );");
 *     Record rcd = get_record(rs, 0);
 *     char * rcd_s = record_to_string(rcd);
 *     int ret = strcmp(rcd_s, "CREATE TABLE SUCCESS");
 *
 *     (2) SELECT语句返回的结果集可能存在多于1条的情况，使用方式：
 *     RecordSet rs = sql_execute("SELECT * FROM table_select_multi ORDER BY id;");
 *     // 取第一行
 *     Record rcd = get_record(rs, 0);
 *     char * rcd_s = record_to_string(rcd);
 *     ret = strcmp(rcd_s, "100, 'Bananas'");
 *     CPPUNIT_ASSERT(ret == 0);
 *     // 取第二行
 *     rcd = get_record(rs, 1);
 *     rcd_s = record_to_string(rcd);
 *     ret = strcmp(rcd_s, "200, 'Apple'");
 *     CPPUNIT_ASSERT(ret == 0);
 *
 * @param rs    : [IN] 查询返回的结果集
 * @param index : [IN] 需要获取的记录的下标，从0开始
 *
 * @return : 结果集rs中的第index条记录
******************************************************************************/
Record get_record(const RecordSet rs, int index);


/******************************************************************************
 * @Description : 将记录转换成字符串，这样就可以便于校验结果
 *                结果记录有两种情况：
 *                (1) CREATE TABLE/DROP TABLE/INSERT INTO 语句返回的结果
 *                    都是提示信息，相当于结果只有一列，是text类型字符串
 *                    例如：CREATE TABLE SUCCESS
 *                (2) SELECT语句返回的结果
 *                    多个值之间用英文逗号','分隔，且逗号后留有一个空格，举例：
 *                    100, 'Bananas'
 *                    200, 'Apple'
 *                    特别注意：text类型的值，需要加英文单引号括起来，如上
 *
 * @param rcd   : [IN] 记录
 *
 * @return : 记录转成的字符串
 *           特别说明：返回的字符串的内存仍然由SQL引擎管理，在函数rm_recordset
 *           中一同释放
******************************************************************************/
char* record_to_string(const Record rcd);


/******************************************************************************
 * @Description : 释放记录集中的所有资源（动态分配的内存）
 *                特别说明，记录集中的内存可能是在下面几种情况下分配的：
 *                1、记录集中的内存主体是在 sql_execute 函数中分配的；
 *                2、在调用 get_record 的时候有可能会分配内存（跟实现方式有关）
 *                3、在调用 record_to_string 的时候会分配内存，也要管理起来
 *
 * @param rcd   : [IN] 记录集
 *
 * @return : 调用此接口后，rs 中的内存会被释放完毕，最后rs的值为NULL
******************************************************************************/
void rm_recordset(RecordSet& rs);


static int type = 0;
static int repeat = 0;
static int repeat_del = 0;
static int row = 0;

/***********************************设计规则 ***********************************
1、支持的数据类型：
	integer : 整型，有符号 4 字节整数；
	text : 变长字符串；（实现的时候，内部可以直接用char*）
2、支持语法：
	SQL关键字(包括数据类型)不区分大小写，表名/列名/列值 区分大小写；
    SQL关键字包括：
		CREATE TABLE/INTEGER/TEXT/DROP TABLE/INSERT INTO/VALUES/ORDER BY/
		SELECT FROM WHERE/ORDER BY/DELETE FROM WHERE
		SQL语句中的特殊字符包括：( ) ' ; =
3、语法细节：
	关于语句返回的错误信息，请参考.h文件定义
	创建表：CREATE TABLE table_name (col1_name   integer,col2_name   text);最大列数为5,列号从1开始
	删除表：DROP TABLE table_name;
	插入记录：INSERT INTO table_name VALUES (100, 'Bananas');允许有重复
	查询记录：SELECT * FROM table_name WHERE col1_name = 100;
			  SELECT * FROM table_name WHERE col2_name = 'Bananas' ORDER BY col1_name;
				1、ORDER BY 以升序排列
				2、当前SELECT关键字后，仅支持*（即返回所有列，列顺序按照创建表时候的列顺序），不需要考虑返回局部列的情况
*********************************************************************************/




//////////////////////////////// 记录集接口定义 ///////////////////////////////

/*****************************************
*	功能:	SQL语句执行接口
*    
*	输入:	const char *sql ：  SQL语句
*    
*	输出:   无输出
*     
*	返回:	SQL语句执行后的结果集，只有SELECT语句返回的结果集可能存在多于1条的情况
*			CREATE TABLE/DROP TABLE/INSERT INTO 语句返回的结果集只有一条记录，
*			反映出当前语句的执行结果 。
*			如CREATE TABLE执行成功后返回CREATE TABLE SUCCESS，失败则返回CREATE TABLE FAILED
*****************************************/


RecordSet sql_execute(const char *sql)
{
    return NULL;
}


/*****************************************
*	功能:	SQL语句执行接口
			从上面 sql_execute 接口已经说明，结果集只有两种类情况：
*			(1) CREATE TABLE/DROP TABLE/INSERT INTO 语句返回的结果集只有一条记录，
*			使用方式如下：
*			RecordSet rs = 
*			sql_execute("CREATE TABLE table_select_multi ( id integer, name text );");
*			Record rcd = get_record(rs, 0);
*			char * rcd_s = record_to_string(rcd);
*			int ret = strcmp(rcd_s, "CREATE TABLE SUCCESS");
*
*			(2) SELECT语句返回的结果集可能存在多于1条的情况，使用方式：
*			RecordSet rs = sql_execute("SELECT * FROM table_select_multi ORDER BY id;");
*			// 取第一行
*			Record rcd = get_record(rs, 0);
*			char * rcd_s = record_to_string(rcd);
*			ret = strcmp(rcd_s, "100, 'Bananas'");
*			CPPUNIT_ASSERT(ret == 0);
*			// 取第二行
*			rcd = get_record(rs, 1);
*			rcd_s = record_to_string(rcd);
*			ret = strcmp(rcd_s, "200, 'Apple'");
*			CPPUNIT_ASSERT(ret == 0);
*    
*	输入:	const RecordSet rs ：  结果集
*			int index ：           行号（行号从0开始）
*    
*	输出:   无输出
*     
*	返回:	结果集rs中的第index条记录
*****************************************/

Record get_record(const RecordSet rs, int index)
{
    return NULL;
}

/******************************************************************************
 * 功能描述 :	  释放记录集中的所有资源（动态分配的内存）
 *                特别说明，记录集中的内存可能是在下面几种情况下分配的：
 *                1、记录集中的内存主体是在 sql_execute 函数中分配的；
 *                2、在调用 get_record 的时候有可能会分配内存（跟实现方式有关）
 *                3、在调用 record_to_string 的时候会分配内存，也要管理起来
 *
 * 输入:		  [IN] 记录集
 *
 * 输出:		  无输出
 *
 * 返回:		  调用此接口后，rs 中的内存会被释放完毕，最后rs的值为NULL
******************************************************************************/

void rm_recordset(RecordSet& rs)
{
    return;
}
/******************************************************************************
 * 功能描述 :	  将记录转换成字符串，这样就可以便于校验结果
 *                结果记录有两种情况：
 *                (1) CREATE TABLE/DROP TABLE/INSERT INTO 语句返回的结果
 *                    都是提示信息，相当于结果只有一列，是text类型字符串
 *                    例如：CREATE TABLE SUCCESS
 *                (2) SELECT语句返回的结果
 *                    多个值之间用英文逗号','分隔，且逗号后留有一个空格，举例：
 *                    100, 'Bananas'
 *                    200, 'Apple'
 *                    特别注意：text类型的值，需要加英文单引号括起来，如上
 *
 * 输入  :		  [IN] 记录
 *
 * 输出  :		  无输出。
 *
 * 返回  :		  记录转成的字符串
 *				  特别说明：返回的字符串的内存仍然由SQL引擎管理，在函数rm_recordset
 *				  中一同释放
******************************************************************************/
char* record_to_string(const Record rcd)
{
    return NULL;
}

int main() {
    //测试 CREATE TABLE : 异常用例，不正确的关键字“CREATETABLE”
    {
        // 创建表
        RecordSet rs = sql_execute("CREATETABLE table_name ( id integer, name text );");
        Record rcd = get_record(rs, 0);
        char * rcd_s = record_to_string(rcd);
        std::cout << (rcd_s != NULL) << std::endl;
        int ret = strcmp(rcd_s, "CREATE TABLE FAILED");
        std::cout << (ret == 0) << std::endl;
        rm_recordset(rs); //清理记录集，确保上面申请的内存不泄露
    }

    // 测试 CREATE TABLE : 异常用例，语法错误“TABLE CREATE”（关键字序列不正确）
    {
        // 创建表
        RecordSet rs = sql_execute("TABLE CREATE table_name ( id integer, name text );");
        Record rcd = get_record(rs, 0);
        char * rcd_s = record_to_string(rcd);
        std::cout << (rcd_s != NULL) << std::endl;
        int ret = strcmp(rcd_s, "CREATE TABLE FAILED");
        std::cout << (ret == 0) << std::endl;
        rm_recordset(rs);
    }

    // 测试 CREATE TABLE : 异常用例，列的数据类型不正确（仅支持integer和text）
    {
        // 创建表
        RecordSet rs = sql_execute("CREATE TABLE table_name ( id bigint, name text );");
        Record rcd = get_record(rs, 0);
        char * rcd_s = record_to_string(rcd);
        std::cout << (rcd_s != NULL) << std::endl;
        int ret = strcmp(rcd_s, "Type:'bigint' is not supported");
        std::cout << (ret == 0) << std::endl;
        rm_recordset(rs); //清理记录集，确保上面申请的内存不泄露
    }

    // 测试 CREATE TABLE : 异常用例，列的数目不能大于5列
    {
        // 创建表
        RecordSet rs = sql_execute("CREATE TABLE table_name ( id1 integer, id2 integer, id3 integer, id4 integer, id5 integer, name text );");
        Record rcd = get_record(rs, 0);
        char * rcd_s = record_to_string(rcd);
        std::cout << (rcd_s != NULL) << std::endl;
        int ret = strcmp(rcd_s, "CREATE TABLE FAILED");
        std::cout << (ret == 0) << std::endl;
        rm_recordset(rs);
    }

    // 测试 CREATE TABLE : 正常创建表和删除表
    {
        // 创建表
        RecordSet rs = sql_execute("CREATE TABLE table_name ( id integer, name text );");
        Record rcd = get_record(rs, 0);
        char * rcd_s = record_to_string(rcd);
        std::cout << (rcd_s != NULL) << std::endl;
        int ret = strcmp(rcd_s, "CREATE TABLE SUCCESS");
        std::cout << (ret == 0) << std::endl;
        rm_recordset(rs);

        // 删除表
        rs = sql_execute("DROP TABLE table_name;");
        rcd = get_record(rs, 0);
        rcd_s = record_to_string(rcd);
        std::cout << (rcd_s != NULL) << std::endl;
        ret = strcmp(rcd_s, "DROP TABLE SUCCESS");
        std::cout << (ret == 0) << std::endl;
        rm_recordset(rs);
    }

    // 测试 CREATE TABLE : 异常用例，重复创建表
    {
        // 创建表
        RecordSet rs = sql_execute("CREATE TABLE table_name2 ( id integer, name text );");
        Record rcd = get_record(rs, 0);
        char * rcd_s = record_to_string(rcd);
        std::cout << (rcd_s != NULL) << std::endl;
        int ret = strcmp(rcd_s, "CREATE TABLE SUCCESS");
        std::cout << (ret == 0) << std::endl;
        rm_recordset(rs);

        // 再次创建表
        rs = sql_execute("CREATE TABLE table_name2 ( id integer, name text );");
        rcd = get_record(rs, 0);
        rcd_s = record_to_string(rcd);
        std::cout << (rcd_s != NULL) << std::endl;
        ret = strcmp(rcd_s, "CREATE TABLE FAILED");
        std::cout << (ret == 0) << std::endl;
        rm_recordset(rs);

        // 删除表
        rs = sql_execute("DROP TABLE table_name2;");
        rcd = get_record(rs, 0);
        rcd_s = record_to_string(rcd);
        std::cout << (rcd_s != NULL) << std::endl;
        ret = strcmp(rcd_s, "DROP TABLE SUCCESS");
        std::cout << (ret == 0) << std::endl;
        rm_recordset(rs);
    }
}


