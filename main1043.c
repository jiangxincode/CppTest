#include<stdio.h>
#include<conio.h>
int main1043()
{
    char NAMEA,NAMEB;
    float MATHA,MATHB,PHYSICSA,PHYSICSB,CHEMSTRYA,CHEMSTRYB,SUMA,SUMB,AVERAGEA,AVERAGEB;
    printf("Input the names of A and B ");
    scanf("%c,%c",&NAMEA,&NAMEB);
    printf("Input the marks of A");
    scanf("%f,%f,%f",&MATHA,&PHYSICSA,&CHEMSTRYA);
    printf("Input the marks of B");
    scanf("%f,%f,%f",&MATHB,&PHYSICSB,&CHEMSTRYB);
    SUMA=MATHA+PHYSICSA+CHEMSTRYA;
    SUMB=MATHB+PHYSICSB+CHEMSTRYB;
    AVERAGEA=SUMA/3;
    AVERAGEB=SUMB/3;
    printf("\nNAME  MATH  PHYSICS  CHEMSTRY  SUM  AVERAGE");
    printf("\n%4c,%5.1f,%8.1f,%9.1f,%4.1f,%8.1f%",NAMEA,MATHA,PHYSICSA,CHEMSTRYA,SUMA,AVERAGEA);
    printf("\n%4c,%5.1f,%8.1f,%9.1f,%4.1f,%8.1f%",NAMEB,MATHB,PHYSICSB,CHEMSTRYB,SUMB,AVERAGEB);
    return 0;
}



