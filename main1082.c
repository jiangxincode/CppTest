#include <stdio.h>
int main1082()
{
    int P,E,A,R;

    for(P=0; P<=9; P++)
        for(E=0; E<=9; E++)
            for(A=0; A<=9; A++)
                for(R=0; R<=9; R++)
                {
                    if((P*1000+E*100+A*10+R)-(A*100+R*10+A)==(P*100+E*10+A))
                        printf("P=%d,E=%d,A=%d,R=%d\n%d-%d=%d\n",P,E,A,R,P*1000+E*100+A*10+R,A*100+R*10+A,P*100+E*10+A);
                }

    return 0;
}
