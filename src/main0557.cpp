//李运生

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>

#include "union_find_set.h"

using namespace std;

#define PI 3.1415926535
#define RADIO 1.0
#define PRECSION 1e-6
#define DATA_SIZE 545

#define THRESHOLD 0.34

struct positioon
{
    double longitude;
    double lantitude;
};


double spherical_distance(struct positioon a, struct positioon b)
{
    double temp,dlon,dlat;
    dlon = fabs((b.longitude - a.longitude))*PI/180;
    dlat = fabs((b.lantitude - a.lantitude))*PI/180;
    temp = (sin(dlat/2)*sin(dlat/2)) + cos(a.lantitude*PI/180) * cos(b.lantitude*PI/180) * (sin(dlon/2)*sin(dlon/2));

    if(fabs(temp-1.0) < PRECSION)
    {
        return temp*RADIO;
    }
    else
    {
        return 2 * atan(sqrt(temp)/sqrt(1-temp)) * RADIO;
    }
}



int main0557()
{
    FILE *in = fopen("data/in.txt", "r");
    FILE *out = fopen("data/out.txt", "w");

    struct positioon data[DATA_SIZE];

    if(in == NULL)
    {
        perror("Can't read the file!");
        exit(-1);
    }

    if(out == NULL)
    {
        perror("Can't write the file!");
        exit(-1);
    }

    for(int i=0; i<DATA_SIZE; i++)
    {
        fscanf(in,"%lf %lf\n", &(data[i].lantitude), &(data[i].longitude));
    }

    union_find_set ufset(DATA_SIZE);

    for(int i=0; i<DATA_SIZE; i++)
    {
        for(int j=i+1; j<DATA_SIZE; j++)
        {
            if(ufset.Find(i) != ufset.Find(j))
            {
                if(spherical_distance(data[i], data[j]) < THRESHOLD)
                {
                    if(ufset.Find(i) < ufset.Find(j))
                    {
                        ufset.Union(ufset.Find(i), ufset.Find(j));
                    }
                    else
                    {
                        ufset.Union(ufset.Find(j), ufset.Find(i));
                    }

                    break;
                }
            }
        }
    }

    for(int i=0; i<DATA_SIZE; i++)
    {
        fprintf(out, "%d %d\n", i, ufset.Find(i));
    }

    for(int i=0; i<DATA_SIZE; i++)
    {
        int count = 0;

        for(int j=0; j<DATA_SIZE; j++)
        {
            if(ufset.Find(j) == i)
            {
                if(count == 0)
                {
                    fprintf(out, "\n\n\n-----------  %d  -------------\n",i);
                }

                fprintf(out, "%d %d %d\n", j, (int)data[j].lantitude, (int)data[j].longitude);
                count ++;
            }
        }
    }

    fclose(in);
    fclose(out);
    system("notepad data/out.txt");
    return 0;
}

