/*
�ɼ�ƽ���֡����������ͼ��㡣
�������ּ��㷽����
1. ֱ�Ӱ��ճɼ����㣻
2. ���յȼ����� A90���� B80���� C70���� D60���� E������
ʵ�ֹ��ܣ�
1. ¼��ɼ���¼��ѧ�֣�
2. ���ճɼ������ǰ���㣻
3. ���յȼ����㵱ǰ���㣻
4. ��յ�ǰ��¼��
5. ������
ͨ����������ʾ�û�����������ִ����Ӧ�Ĺ��ܡ�ע��¼��ɼ���ѧ��Ӧ������ǰ��ɼ��Ļ����ϡ�
ע��
1. ѧ��������ɼ����м�Ȩ��
2. ���յȼ����㼴��������Ƽ��㼨�㣬�����ΪС����
*/
#include <iostream>

using namespace std;

void calc_GPA();

int main2501()
{
    calc_GPA();
    while(1)
    {
        cout << "You want to flush the content or to quit the program(f/q): ";
        char ch;
        cin >> ch;
        if(ch == 'f')
        {
            calc_GPA();
        }
        else
        {
            return 0;
        }
    }
}
void calc_GPA()
{
    float score;
    float sum_score_100=0.0,sum_score_5=0.0; //�ٷ��ƺ������
    short credit,sum_credit=0;
    cout << "Input the score and credit,separate with space(quit with \"-1 -1\"): ";
    cin >> score >> credit;
    while(credit != -1)
    {
        sum_score_100 += score*credit;
        sum_score_5 += (score/10-5)*credit;
        sum_credit += credit;
        cout
        << "Now your weighted average GPA is: "
        << sum_score_100/sum_credit
        <<" Or "
        <<sum_score_5/sum_credit
        << endl;
        cout << endl;
        cout << "Input the score and credit,separate with space,(quit with \"-1 -1\"): ";
        cin >> score >> credit;
    }
}
