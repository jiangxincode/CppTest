--��ʱ��ɾ��ĳ����ʱ����ʾ���޷�ɾ������ 'Orders'����Ϊ�ö�������һ�� FOREIGN KEY Լ�����á�
--ԭ��ܼ򵥲�Ҫ���꣬�������������������ˣ������޷�ɾ�����ڴ�ֻ�����ҵ���Щ�����������˸ñ���ֶ�
--ͨ��ϵͳ�������ܽ����SQL Serverϵͳ�����ṩ�˷ǳ����ƵĹ��ܣ��ܴ������ǲ��Һͽ��������⣩

select fk.name,fk.object_id,OBJECT_NAME(fk.parent_object_id) as referenceTableName
from sys.foreign_keys as fk join sys.objects as o on fk.referenced_object_id=o.object_id
where o.name='COURSE'

exec sp_helpconstraint 'COURSE'

alter table COURSE_SCORE drop constraint FK_COURSE_SCORE_COURSE
--����SQL����ܹ��õ�ĳ������Щ������ã�����Ҳ��ʾ���������ı�����ͨ�������ı������������ִ��������伴��ɾ�������
--ALTER TABLE dbo.�����õı���  DROP CONSTRAINT �����
ALTER TABLE dbo.COURSE_LIST  DROP CONSTRAINT FK_COURSE_LIST_COURSE


USE ѧ���ɼ�����ϵͳ
select * from USERS
select * from STUDENT_INFO
select * from TEACHER_INFO
select * from CET_SCORE
select * from CMPLEV_SCORE


select * from COURSE
select * from COURSE_LIST
select * from COURSE_SCORE

exec sp_mark
exec sp_mark @coursename='��۾���ѧ'
exec sp_order
exec sp_order @coursename='��۾���ѧ'



select * from USERS
select * from STUDENT_INFO
select * from TEACHER_INFO

insert into STUDENT_INFO(STU_ID,STU_NAME)
values('3201223080008','���ӳ�')


delete STUDENT_INFO
WHERE STU_ID='3201223080008'

