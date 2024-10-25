USE master
/*  ������ݿ������ɾ��  */
IF DB_ID('ѧ���ɼ�����ϵͳ') IS NOT NULL
BEGIN
    DROP DATABASE ѧ���ɼ�����ϵͳ
END
/*  ���ݿⲻ��������  */
CREATE DATABASE ѧ���ɼ�����ϵͳ
ON
(
	NAME=ѧ���ɼ�����ϵͳ_data,
	FILENAME='F:\temp\ѧ���ɼ�����ϵͳ_data.mdf',
	SIZE=6,
	MAXSIZE=100,
	FILEGROWTH=10%
)
LOG ON
(
	NAME=ѧ���ɼ�����ϵͳ_log,
	FILENAME='F:\temp\ѧ���ɼ�����ϵͳ_log.ldf',
	SIZE=3,
	MAXSIZE=6,
	FILEGROWTH=10%
)
GO
/*****************************************************************/
/*****************************************************************/
IF DB_ID('ѧ���ɼ�����ϵͳ') IS NOT NULL
	USE ѧ���ɼ�����ϵͳ
/* ������ݱ�USERS������ɾ�� */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'USERS'
)
DROP TABLE USERS
/* ������ݱ�USERS���������� */   
CREATE TABLE USERS
(
	USER_ID CHAR(20) NOT NULL PRIMARY KEY,	--�û�ID
	USER_PASSWORD CHAR(20),	--���볤�ȴ���6��С��10
	USER_TYPE INT	--1Ϊѧ����2Ϊ��ʦ��3Ϊ����Ա	
)
/*****************************************************************/
/*****************************************************************/
/* ������ݱ�STUDENT_INFO������ɾ�� */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'STUDENT_INFO'
)
DROP TABLE STUDENT_INFO
/* ������ݱ�STUDENT_INFO���������� */   
CREATE TABLE STUDENT_INFO
(
	STU_ID CHAR(20) NOT NULL PRIMARY KEY,	--ѧ��ѧ��
	STU_NAME CHAR(20),	--ѧ������
	ENROLLMENT_TIME DATETIME,	--��ѧʱ��
	DEPARTMENT CHAR(20),	--����ѧԺ
	MAJOR CHAR(20),	--����רҵ
	SEX	INT,	--�Ա�0��ʾ�У�1��ʾŮ
	BIRTHDAY DATETIME,	--����
	HOMETOWN VARCHAR(50),	--����
	ADDRESS VARCHAR(50),	--����סַ
	PHONE CHAR(20),	--���˵绰����
	RACE CHAR(20),	--������Ϣ
	PARTY INT,	--������ò��0��ʾ��Ա��1��ʾԤ����Ա��2��ʾ��Ա��3��ʾ����
	DIRECTION VARCHAR(50),	--������Ϣ
	PERSON_ID CHAR(20)	--ѧ�����֤��
)
/*****************************************************************/
/*****************************************************************/
/* ������ݱ�TEACHER_INFO������ɾ�� */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'TEACHER_INFO'
)
DROP TABLE TEACHER_INFO
/* ������ݱ�TEACHER_INFO���������� */   
CREATE TABLE TEACHER_INFO
(
	TEA_ID CHAR(20) NOT NULL PRIMARY KEY,	--��ʦѧ��
	TEA_NAME CHAR(20),	--��ʦ����
	TITLE INT,	--��ʦְ�ƣ�0��ʾ��ʦ��1��ʾ�����ڣ�2��ʾ����
	DEPARTMENT CHAR(20),	--����ѧԺ
	MAJOR CHAR(20),	--����רҵ
	SEX	INT,	--�Ա�0��ʾ�У�1��ʾŮ
	BIRTHDAY DATETIME,	--����
	HOMETOWN VARCHAR(50),	--����
	ADDRESS VARCHAR(50),	--����סַ
	PHONE CHAR(20),	--���˵绰����
	RACE CHAR(20),	--������Ϣ
	PARTY INT,	--������ò��0��ʾ��Ա��1��ʾԤ����Ա��2��ʾ��Ա��3��ʾ����
	DIRECTION VARCHAR(50),	--������Ϣ
	PERSON_ID CHAR(20)	--��ʦ���֤��
)
/*****************************************************************/
/*****************************************************************/
/* ������ݱ�COURSE������ɾ�� */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'COURSE'
)
DROP TABLE COURSE
/* ������ݱ�COURSE���������� */   
CREATE TABLE COURSE
(
	COURSE_ID CHAR(20) NOT NULL PRIMARY KEY,	--�γ̺�
	COURSE_NAME CHAR(20),	--�γ���
	COURSE_TIME CHAR(20),	--�Ͽ�ʱ��Σ������硢���������
	START_DATE DATETIME,	--����ʱ��
	END_DATE DATETIME,	--���ʱ��
	CENT INT,	--�γ�ѧ��
	COURSE_TEACHER CHAR(20),	--�ڿν�ʦ
	REQUIRE VARCHAR(50),	--�γ�Ҫ��
	INSTRUCTION VARCHAR(50),	--������Ϣ
)
/*****************************************************************/
/*****************************************************************/
/* ������ݱ�COURSE_SCORE������ɾ�� */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'COURSE_SCORE'
)
DROP TABLE COURSE_SCORE
/* ������ݱ�COURSE_SCORE���������� */   
CREATE TABLE COURSE_SCORE
(
	STU_ID CHAR(20),	--ѧ��ID
	COURSE_ID CHAR(20),	--�γ̺�
	COURSE_NAME CHAR(20),	--�γ���
	SCORE INT	--�γ̷���
)
/*****************************************************************/
/*****************************************************************/
/* ������ݱ�CET_SCORE������ɾ�� */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'CET_SCORE'
)
DROP TABLE CET_SCORE
/* ������ݱ�CET_SCORE���������� */   
CREATE TABLE CET_SCORE
(
	STU_ID CHAR(20),	--ѧ��ID
	STU_NAME CHAR(20),	--ѧ������
	PERSON_ID CHAR(20),	--ѧ�����֤��
	CET4_STATE INT,	--�ļ�״̬��1��ʾδͨ����2��ʾ��ͨ��
	CET6_STATE INT,	--����״̬��1��ʾδͨ����2��ʾ��ͨ��
	TEST_PLACE CHAR(50),	--���Եص�
	TEST_DATE DATETIME,	--��������
	CET4_SCORE INT,	--�ļ��ɼ�
	CET6_SCORE INT,	--�����ɼ�
	DIRECTION VARCHAR(50)	--������Ϣ
)
/*****************************************************************/
/*****************************************************************/
/* ������ݱ�CMPLEV_SCORE������ɾ�� */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'CMPLEV_SCORE'
)
DROP TABLE CMPLEV_SCORE
/* ������ݱ�CMPLEV_SCORE���������� */   
CREATE TABLE CMPLEV_SCORE
(
	STU_ID CHAR(20),	--ѧ��ID
	STU_NAME CHAR(20),	--ѧ������
	PERSON_ID CHAR(20),	--ѧ�����֤��
	LEVEL1_STATE INT,	--�����һ��״̬��1��ʾδͨ����2��ʾ��ͨ��
	LEVEL2_STATE INT,	--���������״̬��1��ʾδͨ����2��ʾ��ͨ��
	LEVEL3_STATE INT,	--���������״̬��1��ʾδͨ����2��ʾ��ͨ��
	LEVEL4_STATE INT,	--������ļ�״̬��1��ʾδͨ����2��ʾ��ͨ��
	TEST_PLACE CHAR(50),	--���Եص�
	TEST_DATE DATETIME,	--��������
	LEVEL1_SCORE INT,	--�����һ���ɼ�
	LEVEL2_SCORE INT,	--����������ɼ�
	LEVEL3_SCORE INT,	--����������ɼ�
	LEVEL4_SCORE INT,	--������ļ��ɼ�
	DIRECTION VARCHAR(50)	--������Ϣ
)
/*****************************************************************/
/*****************************************************************/
/* ������ݱ�COURSE_LIST������ɾ�� */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'COURSE_LIST'
)
DROP TABLE COURSE_LIST
/* ������ݱ�COURSE_LIST���������� */   
CREATE TABLE COURSE_LIST
(
	COURSE_ID CHAR(20),	--�γ̺�
	COURSE_NAME CHAR(20),	--�γ���
	CLASS_ID CHAR(20),	--�༶��
	COURSE_TEACHER CHAR(20),	--�ڿν�ʦ
	WEEKDAY INT,	--�Ͽ�ʱ�䣬1��ʾ����һ��������7��ʾ������
	DAYHOUR CHAR(20),	--�Ͽ�ʱ��
	BUILDING CHAR(20),	--��ѧ¥��
	ROOM CHAR(20),	--��ʦ��
)
/*****************************************************************/
/*****************************************************************/
/* ������ݱ�LOG������ɾ�� */
IF EXISTS
(
	SELECT * FROM INFORMATION_SCHEMA.TABLES
	WHERE TABLE_NAME = 'LOG'
)
DROP TABLE LOG
/* ������ݱ�LOG���������� */   
CREATE TABLE LOG
(
	MANAGER CHAR(20),	--����������
	DO_DATE DATETIME,	--��������
	DO_WHAT VARCHAR(50),	--��������
)
/*****************************************************************/
/*****************************************************************/
/* �������Ա��Ϣ��Ĭ�Ϲ���ԱΪmanager��Ĭ������Ϊroot */  
INSERT INTO USERS(USER_ID,USER_PASSWORD,USER_TYPE)
VALUES('manager','root',3);
/*****************************************************************/

GO

