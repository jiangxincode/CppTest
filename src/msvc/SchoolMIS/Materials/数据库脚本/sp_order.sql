/*************************************************************/
--�õ������γ̳ɼ�����
--ʹ��exec sp_order @coursename='XXX'
--XXX����ĳ�γ���
--Ĭ�ϵõ����пγ̳ɼ��������γ��������������У�
CREATE PROCEDURE sp_order
@coursename CHAR(20)='all'	--�γ�����
AS
IF(lower(@coursename)!='all')
BEGIN
	/*************************************************************/
	--�ض��γ̷�������
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