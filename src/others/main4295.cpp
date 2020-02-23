/**
 * 找零钱
 * 描述:  我们知道人民币有1、2、5、10、20、50、100这几种面值。
 * 现在给你n(1≤n≤250)元，让你计算换成用上面这些面额表示且总数不超过100张，共有几种。
 * 比如4元，能用4张1元、2张1元和1张2元、2张2元，三种表示方法。
 * 输入:输入有多组，每组一行，为一个整合n。输入以0结束。
 * 输出:输出该面额有几种表示方法。
 * 样例输入:
 * 1
 * 4
 * 0
 * 样例输出:
 * 1
 * 3
 *
 */
#include <stdio.h>

int main()
{
    int s1,s2,s3,s4,s5,s6,s7,n;

    while(scanf("%d",&n)&&n!=0)
    {
        int s=0;

        for(s2=0; s2<=n/2; s2++)
            for(s3=0; s3<=(n-s2*2)/5; s3++)
                for(s4=0; s4<=(n-s2*2-s3*5)/10; s4++)
                    for(s5=0; s5<=(n-s2*2-s3*5-s4*10)/20; s5++)
                        for(s6=0; s6<=(n-s2*2-s3*5-s4*10-s5*20)/50; s6++)
                            for(s7=0; s7<=(n-s2*2-s3*5-s4*10-s5*20-s6*50)/100; s7++)
                            {
                                s1=n-s2*2-s3*5-s4*10-s5*20-s6*50-s7*100;

                                if(s1>=0&&s1+s2+s3+s4+s5+s6+s7<=100)
                                    s++;
                            }

        printf("%d\n",s);
    }

    return 0;
}
