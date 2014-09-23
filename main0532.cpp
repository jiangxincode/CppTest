/*
百度2014校园招聘-研发工程师笔试题
相似度计算用于衡量对象之间的相似度，在数据挖掘，自然语言处理中是一个基础性计算。
在广告检索服务中往往也会判断网民检索Query和广告Adword的主题相似度。
假设Query或者Adword的主题属性定义为一个长度为10000的浮点数组Pr[10000]
（称之为主题概率数组），
其中Pr[i]表示Query或者Adword属于主题Id为i的概率，
而Query和Adword的相似度简化定义为两者主题概率数组的内积，
即sim(Query,Adword)=sum(QueryPr[i]*AdwordPr[i])(0<=i<10000)，
在实际应用场景中，由于大多数主题的概率都为0，所以主题概率数组往往比较稀疏，
在实现时会以一个紧凑型数组topic_info_t[]的方式保存，
其中100<=数组大小<=1000，并按照topic_id递增排列，0<=topic_id<10000,0<topic_pr<1.
struct topic_info_t{
	int topic_id;
	float topic_pr;
};
现在给出Query的topic_info_t数组和N(N>=5000)个Adwords的topic_info_t数组，
现要求出Query与Adwords的相似度最大值，即max(sim(Query,Adword[i]))(0<=i<N).
float max_sim(const vector<topic_info_t> &query_topic_info,
const vector<topic_info_t> adwords_topic_info[],
int adwords_number);
编写代码求时间复杂度最低的算法，并给出时间复杂度分析。
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
