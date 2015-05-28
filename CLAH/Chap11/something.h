#ifndef _CHAP11_SOMETHING_H
#define _CHAP11_SOMETHING_H

double frac(double *fab(int, double*),int nmax,double e1,double e0);
double expi(int n,double x,double e1);
double gammln(double x);
double beta(double x,double y);
double factrl(int n);
double gamm2(double a,double x,double e1,double e0);
double errf(double x);
double chii(double x,int n);
double beta2(double a,double b,double x,double e1);
double studf(double x,int n);
double cbdf(double p,int n,int k);
double bsl1(int n,double x);
double bsl2(int n,double x);
double bsl3(int n,double x);
double bsl4(int n,double x);
double RF(double x,double y,double z);
double RC(double x,double y);
double RD(double x,double y,double z);
double RJ(double x,double y,double z,double p);
double leg1(double a,double b,int n0,double eps,double h0,double(*f)());

double J0(double);
double J1(double);
double I0(double x);
double I1(double x);
double K0(double x);
double K1(double x);
double Y0(double x);
double Y1(double x);
#endif // _CHAP11_SOMETHING_H

