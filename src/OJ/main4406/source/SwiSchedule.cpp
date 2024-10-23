//review
#include<map>
#include<queue>

using namespace std;

class process
{
public:
    int swiId;
    int prio;
    void (*proc)(void);
    friend bool operator <(process proc1,process proc2)// ���������ȶ�������Ҫ���бȽ� ���ĸ����� �������ú��������бȽ�С
    {
        return proc1.prio>proc2.prio;
    }

};

map<int,process> processsavemap;
priority_queue<process> prqueue;
int currentID=100;//�Ժ��жϵ�ǰID

/*************************************************************************************************
����˵�����������ж�
���������
      swiId�� �������ж�ID��
	  prio��  �������ж����ȼ���
      proc��  �������жϴ�������
�����������3
����ֵ  ���ɹ�����0�� �����������-1
**************************************************************************************************/
int SwiCreate(unsigned int swiId, unsigned int prio, void (* proc)(void))
{
    //TODO: ��Ӵ���...
    if(swiId>99||prio>31||proc==NULL)
        return -1;
    process add;
    add.swiId=swiId;
    add.prio=prio;
    add.proc=proc;
    if(processsavemap.count(add.swiId)!=0)//�ж������ǲ��Ǵ��������id
        return -1;
    else
        processsavemap[add.swiId]=add;// ���������������ӽ�map
    return 0;
}

/*************************************************************************************************
����˵�������жϼ���
���������swiId�� ���������ж�ID
�����������
����ֵ  ���ɹ�����0�� �����������-1
**************************************************************************************************/
int SwiActivate(unsigned int swiId)
{
    //TODO: ��Ӵ���...
    if(processsavemap.count(swiId)==0)//��map����û�е�Ȼ�϶�Ҫ����-1
        return -1;
    //��ʼ��ʱ�� swiId���뵽���ȶ������桢�� �����������кõ�����
    prqueue.push(processsavemap[swiId]);
    // ����  һֱ���е����ȶ�������û�е�ʱ��Ϊֹ
    while(!prqueue.empty())
    {
        process topprocess=prqueue.top();
        if(currentID!=topprocess.swiId)
        {
            int beforeID=currentID;
            currentID=topprocess.swiId;
            topprocess.proc();
            currentID=beforeID;
            prqueue.pop();//������
        }
        else
        {
            break;//��ͬһ����ʱ��Ȼ���������� ���ù�
        }
    }
    return 0;
}

/*************************************************************************************************
����˵����������е���Ϣ
�����������
�����������
����ֵ  ����
**************************************************************************************************/
void Clear(void)
{
    //TODO: ��Ӵ���...
    currentID=100;
    processsavemap.clear();
    while(!prqueue.empty())
    {
        prqueue.pop();
    }
}
