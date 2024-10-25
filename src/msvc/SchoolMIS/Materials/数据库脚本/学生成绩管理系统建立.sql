USE master
/*  如果数据库存在则删除  */
IF DB_ID('学生成绩管理系统') IS NOT NULL
BEGIN
    DROP DATABASE 学生成绩管理系统
END
/*  数据库不存在则建立  */
CREATE DATABASE 学生成绩管理系统
ON
(
	NAME=学生成绩管理系统_data,
	FILENAME='F:\temp\学生成绩管理系统_data.mdf',
	SIZE=6,
	MAXSIZE=100,
	FILEGROWTH=10%
)
LOG ON
(
	NAME=学生成绩管理系统_log,
	FILENAME='F:\temp\学生成绩管理系统_log.ldf',
	SIZE=3,
	MAXSIZE=6,
	FILEGROWTH=10%
)
GO
/*****************************************************************/
/*****************************************************************/
IF DB_ID('学生成绩管理系统') IS NOT NULL
	USE 学生成绩管理系统
/* 如果数据表USERS存在则删除 */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'USERS'
)
DROP TABLE USERS
/* 如果数据表USERS不存在则建立 */   
CREATE TABLE USERS
(
	USER_ID CHAR(20) NOT NULL PRIMARY KEY,	--用户ID
	USER_PASSWORD CHAR(20),	--密码长度大于6，小于10
	USER_TYPE INT	--1为学生，2为教师，3为管理员	
)
/*****************************************************************/
/*****************************************************************/
/* 如果数据表STUDENT_INFO存在则删除 */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'STUDENT_INFO'
)
DROP TABLE STUDENT_INFO
/* 如果数据表STUDENT_INFO不存在则建立 */   
CREATE TABLE STUDENT_INFO
(
	STU_ID CHAR(20) NOT NULL PRIMARY KEY,	--学生学号
	STU_NAME CHAR(20),	--学生姓名
	ENROLLMENT_TIME DATETIME,	--入学时间
	DEPARTMENT CHAR(20),	--所在学院
	MAJOR CHAR(20),	--所在专业
	SEX	INT,	--性别，0表示男，1表示女
	BIRTHDAY DATETIME,	--生日
	HOMETOWN VARCHAR(50),	--籍贯
	ADDRESS VARCHAR(50),	--现在住址
	PHONE CHAR(20),	--个人电话号码
	RACE CHAR(20),	--民族信息
	PARTY INT,	--政治面貌，0表示党员，1表示预备党员，2表示团员，3表示其他
	DIRECTION VARCHAR(50),	--其他信息
	PERSON_ID CHAR(20)	--学生身份证号
)
/*****************************************************************/
/*****************************************************************/
/* 如果数据表TEACHER_INFO存在则删除 */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'TEACHER_INFO'
)
DROP TABLE TEACHER_INFO
/* 如果数据表TEACHER_INFO不存在则建立 */   
CREATE TABLE TEACHER_INFO
(
	TEA_ID CHAR(20) NOT NULL PRIMARY KEY,	--教师学号
	TEA_NAME CHAR(20),	--教师姓名
	TITLE INT,	--教师职称，0表示讲师，1表示副教授，2表示教授
	DEPARTMENT CHAR(20),	--所在学院
	MAJOR CHAR(20),	--所在专业
	SEX	INT,	--性别，0表示男，1表示女
	BIRTHDAY DATETIME,	--生日
	HOMETOWN VARCHAR(50),	--籍贯
	ADDRESS VARCHAR(50),	--现在住址
	PHONE CHAR(20),	--个人电话号码
	RACE CHAR(20),	--民族信息
	PARTY INT,	--政治面貌，0表示党员，1表示预备党员，2表示团员，3表示其他
	DIRECTION VARCHAR(50),	--其他信息
	PERSON_ID CHAR(20)	--教师身份证号
)
/*****************************************************************/
/*****************************************************************/
/* 如果数据表COURSE存在则删除 */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'COURSE'
)
DROP TABLE COURSE
/* 如果数据表COURSE不存在则建立 */   
CREATE TABLE COURSE
(
	COURSE_ID CHAR(20) NOT NULL PRIMARY KEY,	--课程号
	COURSE_NAME CHAR(20),	--课程名
	COURSE_TIME CHAR(20),	--上课时间段：如上午、下午和晚上
	START_DATE DATETIME,	--开课时间
	END_DATE DATETIME,	--结课时间
	CENT INT,	--课程学分
	COURSE_TEACHER CHAR(20),	--授课教师
	REQUIRE VARCHAR(50),	--课程要求
	INSTRUCTION VARCHAR(50),	--其他信息
)
/*****************************************************************/
/*****************************************************************/
/* 如果数据表COURSE_SCORE存在则删除 */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'COURSE_SCORE'
)
DROP TABLE COURSE_SCORE
/* 如果数据表COURSE_SCORE不存在则建立 */   
CREATE TABLE COURSE_SCORE
(
	STU_ID CHAR(20),	--学生ID
	COURSE_ID CHAR(20),	--课程号
	COURSE_NAME CHAR(20),	--课程名
	SCORE INT	--课程分数
)
/*****************************************************************/
/*****************************************************************/
/* 如果数据表CET_SCORE存在则删除 */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'CET_SCORE'
)
DROP TABLE CET_SCORE
/* 如果数据表CET_SCORE不存在则建立 */   
CREATE TABLE CET_SCORE
(
	STU_ID CHAR(20),	--学生ID
	STU_NAME CHAR(20),	--学生姓名
	PERSON_ID CHAR(20),	--学生身份证号
	CET4_STATE INT,	--四级状态，1表示未通过，2表示已通过
	CET6_STATE INT,	--六级状态，1表示未通过，2表示已通过
	TEST_PLACE CHAR(50),	--考试地点
	TEST_DATE DATETIME,	--考试日期
	CET4_SCORE INT,	--四级成绩
	CET6_SCORE INT,	--六级成绩
	DIRECTION VARCHAR(50)	--其他信息
)
/*****************************************************************/
/*****************************************************************/
/* 如果数据表CMPLEV_SCORE存在则删除 */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'CMPLEV_SCORE'
)
DROP TABLE CMPLEV_SCORE
/* 如果数据表CMPLEV_SCORE不存在则建立 */   
CREATE TABLE CMPLEV_SCORE
(
	STU_ID CHAR(20),	--学生ID
	STU_NAME CHAR(20),	--学生姓名
	PERSON_ID CHAR(20),	--学生身份证号
	LEVEL1_STATE INT,	--计算机一级状态，1表示未通过，2表示已通过
	LEVEL2_STATE INT,	--计算机二级状态，1表示未通过，2表示已通过
	LEVEL3_STATE INT,	--计算机三级状态，1表示未通过，2表示已通过
	LEVEL4_STATE INT,	--计算机四级状态，1表示未通过，2表示已通过
	TEST_PLACE CHAR(50),	--考试地点
	TEST_DATE DATETIME,	--考试日期
	LEVEL1_SCORE INT,	--计算机一级成绩
	LEVEL2_SCORE INT,	--计算机二级成绩
	LEVEL3_SCORE INT,	--计算机三级成绩
	LEVEL4_SCORE INT,	--计算机四级成绩
	DIRECTION VARCHAR(50)	--其他信息
)
/*****************************************************************/
/*****************************************************************/
/* 如果数据表COURSE_LIST存在则删除 */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'COURSE_LIST'
)
DROP TABLE COURSE_LIST
/* 如果数据表COURSE_LIST不存在则建立 */   
CREATE TABLE COURSE_LIST
(
	COURSE_ID CHAR(20),	--课程号
	COURSE_NAME CHAR(20),	--课程名
	CLASS_ID CHAR(20),	--班级号
	COURSE_TEACHER CHAR(20),	--授课教师
	WEEKDAY INT,	--上课时间，1表示星期一，……，7表示星期日
	DAYHOUR CHAR(20),	--上课时间
	BUILDING CHAR(20),	--教学楼号
	ROOM CHAR(20),	--教师号
)
/*****************************************************************/
/*****************************************************************/
/* 如果数据表LOG存在则删除 */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'LOG'
)
DROP TABLE LOG
/* 如果数据表LOG不存在则建立 */   
CREATE TABLE LOG
(
	MANAGER CHAR(20),	--操作者姓名
	DO_DATE DATETIME,	--操作日期
	DO_WHAT VARCHAR(50),	--操作内容
)
/*****************************************************************/
/*****************************************************************/
/* 插入管理员信息，默认管理员为manager，默认密码为root */  
INSERT INTO USERS(USER_ID,USER_PASSWORD,USER_TYPE)
VALUES('manager','root',3);
/*****************************************************************/

GO

