#ifndef COMMON_DEF_H
#define COMMON_DEF_H

//A�������������
#define MAX_WAITTING_ATASK 100

enum TaskType
{
	ATask,			//A������
	BTask,			//B������
	CTask,			//C������
	NTask = 255		//��Ч����
};

enum OperateType
{
	AddTask,		//��������
    RunTask,		//��������
	DelTask,		//ɾ������
	DelForceTask,	//ǿ��ɾ������
	ClearTask		//���һ������	
};

enum TaskStatus
{
	Waiting,    //���񱻴���������δ����״̬
	Finished,   //�������н������ȴ���ɾ��
	NotExist    //�����Ѿ���ɾ����δ������������Ҳ�Ǵ�״̬
};

typedef unsigned int TaskID;

#endif