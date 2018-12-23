--有时想删除某个表时，提示“无法删除对象 'Orders'，因为该对象正由一个 FOREIGN KEY 约束引用”
--原因很简单不要急躁，它被其它表的外键引用了，所以无法删除，在此只需先找到哪些表的外键引用了该表的字段
--通过系统函数就能解决（SQL Server系统函数提供了非常完善的功能，能代替我们查找和解决许多问题）

select fk.name,fk.object_id,OBJECT_NAME(fk.parent_object_id) as referenceTableName
from sys.foreign_keys as fk join sys.objects as o on fk.referenced_object_id=o.object_id
where o.name='COURSE'

exec sp_helpconstraint 'COURSE'

alter table COURSE_SCORE drop constraint FK_COURSE_SCORE_COURSE
--以上SQL语句能够得到某个表被哪些外键引用，并且也显示出了外键表的表名。通过外键表的表名和外键名称执行以下语句即可删除外键。
--ALTER TABLE dbo.被引用的表名  DROP CONSTRAINT 外键名
ALTER TABLE dbo.COURSE_LIST  DROP CONSTRAINT FK_COURSE_LIST_COURSE


USE 学生成绩管理系统
select * from USERS
select * from STUDENT_INFO
select * from TEACHER_INFO
select * from CET_SCORE
select * from CMPLEV_SCORE


select * from COURSE
select * from COURSE_LIST
select * from COURSE_SCORE

exec sp_mark
exec sp_mark @coursename='宏观经济学'
exec sp_order
exec sp_order @coursename='宏观经济学'



select * from USERS
select * from STUDENT_INFO
select * from TEACHER_INFO

insert into STUDENT_INFO(STU_ID,STU_NAME)
values('3201223080008','凌子超')


delete STUDENT_INFO
WHERE STU_ID='3201223080008'

