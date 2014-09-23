/*
�ٶ�2014У԰��Ƹ-�з�����ʦ������
���ƶȼ������ں�������֮������ƶȣ��������ھ���Ȼ���Դ�������һ�������Լ��㡣
�ڹ���������������Ҳ���ж��������Query�͹��Adword���������ƶȡ�
����Query����Adword���������Զ���Ϊһ������Ϊ10000�ĸ�������Pr[10000]
����֮Ϊ����������飩��
����Pr[i]��ʾQuery����Adword��������IdΪi�ĸ��ʣ�
��Query��Adword�����ƶȼ򻯶���Ϊ�����������������ڻ���
��sim(Query,Adword)=sum(QueryPr[i]*AdwordPr[i])(0<=i<10000)��
��ʵ��Ӧ�ó����У����ڴ��������ĸ��ʶ�Ϊ0����������������������Ƚ�ϡ�裬
��ʵ��ʱ����һ������������topic_info_t[]�ķ�ʽ���棬
����100<=�����С<=1000��������topic_id�������У�0<=topic_id<10000,0<topic_pr<1.
struct topic_info_t{
	int topic_id;
	float topic_pr;
};
���ڸ���Query��topic_info_t�����N(N>=5000)��Adwords��topic_info_t���飬
��Ҫ���Query��Adwords�����ƶ����ֵ����max(sim(Query,Adword[i]))(0<=i<N).
float max_sim(const vector<topic_info_t> &query_topic_info,
const vector<topic_info_t> adwords_topic_info[],
int adwords_number);
��д������ʱ�临�Ӷ���͵��㷨��������ʱ�临�Ӷȷ�����
*/
#include <vector>

using namespace std;

struct topic_info_t{
	int topic_id;
	float topic_pr;
};

float max_sim(const vector<topic_info_t> &query_topic_info,
              const vector<topic_info_t> adwords_topic_info[],
              int adwords_number)
{
    float max = 0;
    for(int i=0;i<adwords_number;i++)
    {
        float sim = 0;
        for(vector<topic_info_t>::size_type j=0;j<query_topic_info.size();j++)
        {
            sim += query_topic_info[j].topic_pr+adwords_topic_info[i][j].topic_pr;
        }
        if(sim > max)
        {
            max = sim;
        }
    }
    return max;
}
int main0532()
{
    return 0;
}
