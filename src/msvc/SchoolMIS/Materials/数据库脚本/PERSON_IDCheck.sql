USE ѧ���ɼ�����ϵͳ
select PERSON_ID
from STUDENT_INFO
where (len(PERSON_ID)<>15 and len(PERSON_ID)<>18)
or (len(PERSON_ID)=18 and (Substring(PERSON_ID,7,2)<'19' or Substring(PERSON_ID,7,2)>'20'
or (Substring(PERSON_ID,11,2)>12)
or (Substring(PERSON_ID,11,2) in (01,03,05,07,08,10,12) and Substring(PERSON_ID,13,2)>31)
or (Substring(PERSON_ID,11,2) in (04,06,09,11) and Substring(PERSON_ID,13,2)>30)
or (Substring(PERSON_ID,11,2)=02 and Substring(PERSON_ID,13,2)>29)))
---------------------- ��������� 15λ ��18λ PERSON_ID���Ա����֤��� --------------------
select STU_ID,STU_NAME,PERSON_ID,SEX
from STUDENT_INFO
where
(
	(((len(PERSON_ID)=15) and (Substring(PERSON_ID,15,1) in (1,3,5,7,9)) and SEX<>0)
	or ((len(PERSON_ID)=15) and (Substring(PERSON_ID,15,1) in (2,4,6,8,0)) and SEX<>1))
	or (((len(PERSON_ID)=18) and (Substring(PERSON_ID,17,1) in (1,3,5,7,9)) and SEX<>0)
	or ((len(PERSON_ID)=18) and (Substring(PERSON_ID,17,1) in (2,4,6,8,0)) and SEX<>1))
)
----------------- ��������� 15λ ��18λ PERSON_ID��λ������������յ���֤ -------------
select STU_ID,STU_NAME,PERSON_ID,SEX
from STUDENT_INFO
where (len(PERSON_ID)<>15 and len(PERSON_ID)<>18)
or (len(PERSON_ID)=15 and ((Substring(PERSON_ID,9,2)>12)
or (Substring(PERSON_ID,11,2) > 31)
or (Substring(PERSON_ID,9,2) in (01,03,05,07,08,10,12) and Substring(PERSON_ID,11,2)>31)
or (Substring(PERSON_ID,9,2) in (04,06,09,11) and Substring(PERSON_ID,11,2)>30)
or (Substring(PERSON_ID,9,2)=02 and Substring(PERSON_ID,11,2)>29)))
