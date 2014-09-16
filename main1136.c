/*找出一个二维数组中的所有鞍点并输出。
  若一个数组元素的值是所在行的最大值，同时是所在列的最小值，该数组元素就是鞍点。
  一个二维数组中可能没有鞍点，也可能有多个鞍点。
  编程要求： 编写main函数。声明一个二维数组a并用测试矩阵初始化，在数组a中查找鞍点,输出找到的所有鞍点位置。
  测试矩阵:
       1    2    3    4
       5    6    7    8
       9   10  11   12
       13 14  15   16
    输出结果：
      The saddle point is：a[0][3]
*/
#include<stdio.h>
main1136()
{
    int i,j,k,t=0,max,maxj;
    int a[4][4]= {{1,2,3,4,},{5,6,7,8},{9,10,11,12},{13,14,15,16}};

    for(i=0; i<4; i++)
    {
        max=a[i][0];
        j=0;

        for(j=0; j<4; j++)
            if(a[i][j]>max)
                max=a[i][j],maxj=j;

        for(k=0; k<4; k++)
            if(a[k][maxj]<max)
                break;

        if(k>=4)
        {
            printf("The saddle point is a[%d][%d]\n",i,maxj);
            t=1;
        }
    }

    if(t==0) printf("There is no saddle point!\n");
}
