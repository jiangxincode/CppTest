/**
 * 会议中心
 * Siruseri政府建造了一座新的会议中心。许多公司对租借会议中心的会堂很感兴趣，他们希望能够在里面举行会议。 对于一个客户而言，仅当在开会时能够独自占用整个会堂，他才会租借会堂。会议中心的销售主管认为：最好的策略应该是将会堂租借给尽可能多的客户。显然，有可能存在不止一种满足要求的策略。 例如下面的例子。总共有4个公司。他们对租借会堂发出了请求，并提出了他们所需占用会堂的起止日期（如下表所示）。
 * 开始日期	结束日期
 * 公司1	4	9
 * 公司2	9	11
 * 公司3	13	19
 * 公司4	10	17
 *
 * 上例中，最多将会堂租借给两家公司。租借策略分别是租给公司1和公司3，或是公司2和公司3，也可以是公司1和公司4。注意会议中心一天最多租借给一个公司，所以公司1和公司2不能同时租借会议中心，因为他们在第九天重合了。
 * 销售主管为了公平起见，决定按照如下的程序来确定选择何种租借策略：首先，将租借给客户数量最多的策略作为候选，将所有的公司按照他们发出请求的顺序编号。对于候选策略，将策略中的每家公司的编号按升序排列。最后，选出其中字典序最小1的候选策略作为最终的策略。 例中，会堂最终将被租借给公司1和公司3：3个候选策略是{(1,3),(2,3),(1,4)}。而在字典序中(1,3)<(1,4)<(2,3)<>。 你的任务是帮助销售主管确定应该将会堂租借给哪些公司。<(1,4)<(2,3)<><(1,4)<(2,3)<><(1,4)<(2,3)<></(1,4)<(2,3)<><(1,4)<(2,3)<></(1,4)<(2,3)<><(1,4)<(2,3)<></(1,4)<(2,3)<>
 * 对于50%的输入，N≤3000。在所有输入中，N≤200000。
 * -------------------
 * 1 字典序指在字典中排列的顺序，如果序列l1是序列l2的前缀，或者对于l1和l2的第一个不同位置j，l1[j]<L2[J]<>，则l1比l2小。</L2[J]<>
 *
 * •	接口说明
 * 原型：
 * void ConferenceArrangement(unsigned int nCompany, CompanyRequest * pCompanyRequest, unsigned int * nCompanyOut, unsigned int * pArrIndex);
 * 输入参数：
 *     nCompany           参加申请的公司数
 *     pCompanyRequest  每个公司请求使用的起止时间
 * 其中结构体：
 * struct CompanyRequest
 * {
 *     int nBegin;
 *     int nEnd;
 * };
 * 代表每个公司申请的起始日期
 * 输出参数（指针指向的内存区域保证有效）：
 *     nCompanyOut     最多安排公司的个数（出参）
 *     pArrIndex    安排公司的索引数组（出参）
 * 返回值：
 *         Int 1代表成功，0代表失败
 *
 * <L2[J]<></L2[J]<>


 *
 */
#include "iostream"

//CompanyRequest结构体，包含每个公司的申请时间的起始
struct CompanyRequest
{
    int nBegin;
    int nEnd;
};

/**
 * 参考：http://blog.csdn.net/whjpji/article/details/7409646
 */
int ConferenceArrangement(unsigned int nCompany, CompanyRequest* pCompanyRequest, unsigned int * nCompanyOut,  unsigned int* pArrIndex)
{

    return 1;
}

int main()
{
    //输入
    unsigned int nCompanyIn = 4;
    CompanyRequest req[] = {{4,9},
                            {9,11},
                            {13,19},
                            {10,17}};

    //期望输出
    int nCompanyOutTest = 2;
    int ArrIndexTest[] = {1,3};

    //实际输出
    unsigned int nCompanyOut = 0;
    unsigned int ArrIndex[4]={0};


    int res = ConferenceArrangement(nCompanyIn, req, &nCompanyOut, ArrIndex);


    std::cout << (1 == res) << std::endl;
    std::cout << (nCompanyOutTest == nCompanyOut) << std::endl;
    for (int i = 0; i < nCompanyOutTest; i++)
    {
        std::cout << (ArrIndexTest[i] == ArrIndex[i]) << std::endl;
    }


}
