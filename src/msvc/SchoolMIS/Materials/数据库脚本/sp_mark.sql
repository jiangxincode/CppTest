/*************************************************************/
--�õ������γ̵�ƽ���֡���߷֡���ͷ֡������ʡ�������
--ʹ��exec sp_mark @coursename='XXX'
--XXX����ĳ�γ���
--Ĭ��������пγ̵�ƽ���֡���߷֡���ͷ�
CREATE PROCEDURE sp_mark
@coursename CHAR(20)='all'	--�γ�����
AS
DECLARE @coursenid CHAR(20)	--�γ�ID
DECLARE @average INT	--�γ�ƽ����
DECLARE @maximum INT	--�γ���߷�
DECLARE @minimum INT	--�γ���ͷ�
DECLARE @passnum INT	--�γ̼�������
DECLARE @passrate decimal(5,2)	--�γ̼�����
DECLARE @excellentnum INT	--�γ���������
DECLARE @excellentrate decimal(5,2)	--�γ�������
DECLARE @sum INT	--������

IF(lower(@coursename)!='all')
	BEGIN
	/*************************************************************/
	--ȡ��������
	SELECT @sum=COUNT(SCORE)
	FROM COURSE_SCORE
	WHERE COURSE_NAME=@coursename
	/*************************************************************/

	/*************************************************************/
	--���ƽ���֡���߷֡���ͷ�
	SELECT @average=AVG(SCORE),@maximum=MAX(SCORE),@minimum=MIN(SCORE)
	FROM COURSE_SCORE
	WHERE COURSE_NAME=@coursename
	/*************************************************************/

	/*************************************************************/
	--���������
	SELECT @passnum=COUNT(SCORE)
	FROM COURSE_SCORE
	WHERE SCORE>60 AND COURSE_NAME=@coursename
	SELECT @passrate=CONVERT(decimal(5,2),@passnum)/CONVERT(decimal(5,2),@sum)
	/*************************************************************/

	/*************************************************************/
	--���������
	SELECT @excellentnum=COUNT(SCORE)
	FROM COURSE_SCORE
	WHERE SCORE>90 AND COURSE_NAME=@coursename
	SELECT @excellentrate=CONVERT(decimal(5,2),@excellentnum)/CONVERT(decimal(5,2),@sum)
	/*************************************************************/
	/*************************************************************/
	--��ӡ
	SELECT @coursename AS '�γ�',@average AS ƽ����,@maximum AS ��߷�,@minimum AS ��ͷ�,@passrate AS ������,@excellentrate AS ������
	/*************************************************************/
	END
ELSE
	BEGIN
	SELECT COURSE_NAME AS '�γ�',AVG(SCORE) AS ƽ����,MAX(SCORE) AS ��߷�,MIN(SCORE) AS ��ͷ�
	FROM COURSE_SCORE
	GROUP BY COURSE_NAME
	END