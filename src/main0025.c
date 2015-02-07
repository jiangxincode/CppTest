#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#define MAX_PART_SIZE 3 //ͣ�������ͣ������
#define PRIZE 6.00 //ͣ��ÿСʱ����

/**
 * ͣ��������
 * ��ͣ������һ����ͣ��n����������ͨ������ֻ��һ�����ſɹ�����������
 * ��ͣ�����ڣ�������������Ⱥ�����ɱ������������У�������������϶ˣ���
 * ����������ͣ��n�������������������������ı���ϵȺ򣬵��г�����ʱ������ϵĵ�һ�������ɿ��롣
 * ��ͣ������ĳ����Ҫ�뿪ʱ������֮�����ĳ����������˳�����Ϊ����·�����������������ź����������ٰ�ԭ���򷵻س�����
 * ÿ�����뿪ͣ����ʱ��Ӧ����ͣ��ʱ��ĳ��̽��ѣ��ڱ����ͣ����ʱ�䲻�շѣ���
 * �Ա�д����ģ������������̡�
 * Ҫ����˳��ջģ��ͣ��������������ģ������
 * ���ն˶��������������ȥ�����ݣ�ÿ�����ݰ������
 * 1���ǡ�������ǡ���ȥ����
 * 2���������պ��룻
 * 3�����������ȥ����ʱ�̡�
 * ��ÿ��������Ϣ��Ӧ�������ϢΪ��
 * ����ǵ���ĳ��������������ͣ�����л����ϵ�λ�ã�
 * �������ȥ�ĳ��������������ͣ������ͣ����ʱ���Ӧ�ɵķ��á�
����ʾ��������һ��ջ����ʱͣ��Ϊ��·���ӳ����˳��ĳ���
 */


/**����˳��ջ-ģ��ͣ����*/
typedef struct STACK
{
    long pos[MAX_PART_SIZE]; //�洢���ƺ���
    int time[MAX_PART_SIZE]; //�洢���복վ��ʱ��
    int point; //���һ������λ��ָ��
} Stack;


/**����������-ģ��ͣ������*/
typedef struct queue
{
    int num; //�洢���ƺ�
    struct queue *next; //ָ����һ����
} Queue;


/**��ʼ��ջ*/
void static InitStack(Stack *s)
{
    s->point=-1;
}

/**��ʼ������*/
Queue *InitQueue()
{
    Queue *q;
    q=(Queue *)malloc(sizeof(Queue));
    q->next=NULL;
    return q;
}

/**��ջ����*/
int StackPop(Stack *s,long *i,int *j)
{
    if(s->point==-1)
    {
        return false;
    }
    else
    {
        *i=s->pos[s->point];
        *j=s->time[s->point];
        s->point--;
        return true;
    }
}

/**ѹջ����*/
int StackPush(Stack *s,long i,int j)
{
    if(s->point==MAX_PART_SIZE-1)
    {
        return false;
    }
    else
    {
        s->point++;
        s->pos[s->point]=i;
        s->time[s->point]=j;
        return true;
    }
}

/**�˶Ӻ���*/
int QueuePop(Queue **qH,long *i)
{
    Queue *temp;

    if((*qH)->next==NULL)return false;
    else
    {
        temp=(*qH)->next;
        (*qH)->next=temp->next;
        *i=temp->num;
        free(temp);
        return true;
    }
}

/**��Ӻ���*/
int QueuePush(Queue **q,long i)
{
    Queue *temp;

    if((temp=(Queue *)malloc(sizeof(Queue)))==NULL)return false;
    else
    {
        (*q)->next=temp;
        temp->num=i;
        temp->next=NULL;
        *q=temp;
        return true;
    }
}


int main0025()
{
    int time,i,j;
    long num;
    Stack part;
    Queue *H,*p,*temp,*temp2;
    H=InitQueue();
    p=H;
    InitStack(&part);//��ʼ�����к�ջ
    printf("������ͣ�����������\n");
    printf("\nͣ���������ͣ��%d��,����ͣ���ĵ���ΪÿСʱ%.2fԪ\n",MAX_PART_SIZE,PRIZE);

    while(1)
    {
        int inStack = 0;
        int inQueue = 0;
        temp=H;
        printf("\n--------------------ͣ��������ϵͳ---------------------------\n");
        printf("��ѡ��\n\n\t\t(A��a)����������ѵ�������ѯ\n\t\t(L��l)�����뿪\n\t\t(Q��q)�����˳�\n");
        printf("\n-------------------------------------------------------------\n����ѡ����:");
        char state = getche();

        if(state=='a'||state=='A'||state=='l'||state=='L')
        {
            printf("\n���복�ƺ�(����):");
            scanf("%ld",&num);
            printf("\n���뵽����뿪�ĵ�ʱ��(24Сʱ��,��λ:Сʱ):");
            scanf("%d",&time);
        }

        if(state=='a'||state=='A')
        {
            for(i=0; i<=part.point; i++)
                if(part.pos[i]==num)
                {
                    inStack=1;
                    break;
                }//�ڳ�վ�в���

            for(j=1; temp->next!=NULL; j++)
            {
                temp2=temp;
                temp=temp2->next;

                if(temp->num==num)
                {
                    inQueue=1;
                    break;
                }
            }//�ڳ�վ�����

            if(inStack)
                printf("\n��ѯ���:����������Ѿ��ڳ�վ�е�%d��λ��ͣ����%d��Сʱ!\n",i+1,time-part.time[i]);
            else if(inQueue)
                printf("\n��ѯ���:����������Ѿ��ڳ�վ���%d��λ�õȺ�\n",j);
            else
            {
                if(StackPush(&part,num,time)==false)
                {
                    QueuePush(&p,num);
                    printf("\n��վ����,����ͣ�ڳ��⡣\n");
                }
                else printf("\n�����ɹ���վ!\n");
            }//��������������վ������ͣ�ڳ�վ�⣬���򣬽��복վ
        }
        else if(state=='l'||state=='L')     //������뿪
        {
            for(i=0; i<=part.point; i++)
                if(part.pos[i]==num)
                {
                    inStack=1;
                    break;
                }//�ڳ�վ�в���

            if(inStack)   //����ڳ�վ��
            {
                printf("\n��Ҫ�뿪�������ڳ�վ�е�%d��λ��ͣ����%d��Сʱ,Ӧ��%.2fԪ\n",i+1,time-part.time[i],(time-part.time[i])*PRIZE);

                while(i<part.point)
                {
                    part.pos[i]=part.pos[i+1];
                    part.time[i]=part.time[i+1];
                    i++;
                }

                part.point--;//���뿪�ĳ����ӳ�վ��ɾ��

                if(H->next!=NULL)
                {
                    QueuePop(&H,&num);

                    if(H->next==NULL)p=H;

                    StackPush(&part,num,time);
                    printf("\nͣ�����ճ�һλ�á�����Ⱥ��%ld��������վ��!\n",num);
                }//�����վ���г�����վ
            }
            else     //���ڳ�վ��
            {
                for(i=1; temp->next!=NULL; i++)
                {
                    temp2=temp;
                    temp=temp2->next;

                    if(temp->num==num)
                    {
                        inQueue=1;
                        break;
                    }
                }//�����Ƿ��ڳ�վ��

                if(inQueue)
                {
                    printf("\n����%d��ͣ������,���շ�\n",i);
                    temp2->next=temp->next;

                    if(temp==p)p=temp2;

                    free(temp);
                }//�ڳ�վ��
                else printf("\n����!�������˲����ڵĳ��ƺ�!\n");//������ڳ�վ�⣬˵�����복��������
            }
        }
        else if(state=='q'||state=='Q')
        {
            printf("\n");
            break;
        }
        else printf("\n�������!\n");
    }//end while

    return 0;
}

