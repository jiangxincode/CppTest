#include "../utility.h"

int mde_example5()
{
    int L,j;
    double *rand;
    double x,mean,adev,sddev,var,skew,kurt;
    L=100;  /*生成100个随机数*/
    rand=(double*)malloc(sizeof(double)*L);

    if(rand==NULL)
    {
        printf("memory alloc failed.\n");
        exit(0);
    }

    for(j=0; j<L; j++)
    {
        x=PI*j/L;
        rand[j]=sin(x);
    }

    mde(rand,L,&mean,&adev,&sddev,&var,&skew,&kurt);
    printf("Mean:    %1.5f\n",mean);
    printf("adev:    %1.5f\n",adev);
    printf("sddev:   %1.5f\n",sddev);
    printf("var:     %1.5f\n",var);
    printf("skew:    %1.5f\n",skew);
    printf("kurt:    %1.5f\n",kurt);
    return 0;
}
