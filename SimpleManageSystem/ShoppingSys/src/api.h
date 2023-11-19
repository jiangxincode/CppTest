#ifndef __API_H__
#define __API_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define INIT_MONEY 3000 //��ʼ���
#define INIT_SCORE 150 //��ʼ����
#define MAX_ORDER_NUM 5 //�����Ʒ��������
#define MAX_GOOD_NUM 100 //�����Ʒ����
#define GOOD_TYPE_AMOUNT 3 //�ɹ�ѡ�����Ʒ����


//���ز�����Ϣ
enum OP_RST_INFO
{
    S001,        //��ʼ���ɹ�
    S002,        //�����Ѿ����뵽���ﳵ
    S003,        //�����Ѵӹ��ﳵ��ɾ��

    E001,        //�Ƿ�����
    E002,        //��������
    E003,        //���ﳵ����
    E004,        //��ɾ���Ķ���������
    E005,        //���ﳵ��û����Ʒ����
    E006,        //���￨������ֲ���
};

//��Ʒ����
enum GOOD_TYPE
{
    G_FOOD,      //ʳƷ
    G_CLOTHING,  //��װ
    G_BOOK,      //�鼮
};

//�Żݷ���
enum DISCOUNT_TYPE
{
    D_NO_DISCOUNT, //���Ż�
    D_DISCOUNT, //����
    D_REDUCE, //ֱ��
};

void api_print_result(OP_RST_INFO enResultCode);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __API_H__ */