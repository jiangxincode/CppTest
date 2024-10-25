/*************************************************************/
--得到各个课程成绩排名
--使用exec sp_order @coursename='XXX'
--XXX代表某课程名
--默认得到所有课程成绩排名（课程名按照音序排列）
CREATE PROCEDURE sp_order
@coursename CHAR(20)='all'	--课程名称
AS
IF(lower(@coursename)!='all')
BEGIN
	/*************************************************************/
	--特定课程分数排名
	SELECT STU_ID,COURSE_NAME,SCORE
	FROM COURSE_SCORE
	WHERE COURSE_NAME=@coursename
	ORDER BY SCORE DESC
END
ELSE
BEGIN
	SELECT STU_ID,COURSE_NAME,SCORE
	FROM COURSE_SCORE
	ORDER BY COURSE_NAME DESC,SCORE DESC
END