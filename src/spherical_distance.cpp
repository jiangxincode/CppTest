/**
 * http://blog.csdn.net/zhengnanlee/article/details/8711886
 */
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

#define PI 3.1415926535
#define RADIO 1.0
#define PRECSION 1e-6

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
