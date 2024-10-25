/*************************************************************/
--得到各个课程的平均分、最高分、最低分、及格率、优秀率
--使用exec sp_mark @coursename='XXX'
--XXX代表某课程名
--默认求出所有课程的平均分、最高分、最低分
CREATE PROCEDURE sp_mark
@coursename CHAR(20)='all'	--课程名称
AS
DECLARE @coursenid CHAR(20)	--课程ID
DECLARE @average INT	--课程平均分
DECLARE @maximum INT	--课程最高分
DECLARE @minimum INT	--课程最低分
DECLARE @passnum INT	--课程及格人数
DECLARE @passrate decimal(5,2)	--课程及格率
DECLARE @excellentnum INT	--课程优秀人数
DECLARE @excellentrate decimal(5,2)	--课程优秀率
DECLARE @sum INT	--总人数

IF(lower(@coursename)!='all')
	BEGIN
	/*************************************************************/
	--取得总人数
	SELECT @sum=COUNT(SCORE)
	FROM COURSE_SCORE
	WHERE COURSE_NAME=@coursename
	/*************************************************************/

	/*************************************************************/
	--求出平均分、最高分、最低分
	SELECT @average=AVG(SCORE),@maximum=MAX(SCORE),@minimum=MIN(SCORE)
	FROM COURSE_SCORE
	WHERE COURSE_NAME=@coursename
	/*************************************************************/

	/*************************************************************/
	--求出及格率
	SELECT @passnum=COUNT(SCORE)
	FROM COURSE_SCORE
	WHERE SCORE>60 AND COURSE_NAME=@coursename
	SELECT @passrate=CONVERT(decimal(5,2),@passnum)/CONVERT(decimal(5,2),@sum)
	/*************************************************************/

	/*************************************************************/
	--求出优秀率
	SELECT @excellentnum=COUNT(SCORE)
	FROM COURSE_SCORE
	WHERE SCORE>90 AND COURSE_NAME=@coursename
	SELECT @excellentrate=CONVERT(decimal(5,2),@excellentnum)/CONVERT(decimal(5,2),@sum)
	/*************************************************************/
	/*************************************************************/
	--打印
	SELECT @coursename AS '课程',@average AS 平均分,@maximum AS 最高分,@minimum AS 最低分,@passrate AS 及格率,@excellentrate AS 优秀率
	/*************************************************************/
	END
ELSE
	BEGIN
	SELECT COURSE_NAME AS '课程',AVG(SCORE) AS 平均分,MAX(SCORE) AS 最高分,MIN(SCORE) AS 最低分
	FROM COURSE_SCORE
	GROUP BY COURSE_NAME
	END