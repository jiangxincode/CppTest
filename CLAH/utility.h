#ifndef _UTILITY_H
#define _UTILITY_H

//Chapter02
#define PI 3.1415926

struct c_comp
{
    double rmz; //real part
    double imz; //imaginary part
} c_comp;

int c_comp_plus(struct c_comp *a1,struct c_comp *a2,struct c_comp *c);
int c_comp_sub(struct c_comp *a1,struct c_comp *a2,struct c_comp *c);
int c_comp_product(struct c_comp *a1,struct c_comp *a2,struct c_comp *c);
int c_comp_divide(struct c_comp *a1,struct c_comp *a2,struct c_comp *c);
int c_comp_power(struct c_comp *a,struct c_comp *c,int n);
int c_comp_nthroot(struct c_comp *a,struct c_comp *c,int n);
int c_comp_exp(struct c_comp *a,struct c_comp *c);
int c_comp_log(struct c_comp *a,struct c_comp *c);
int c_comp_sin(struct c_comp *a,struct c_comp *c);
int c_comp_cos(struct c_comp *a,struct c_comp *c);



//Chapter03
int c2p(struct c_comp *a,int n,struct c_comp *y);
int p2c(struct c_comp *y,int n,struct c_comp *a);
int cpmul(struct c_comp *a,int n,struct c_comp *b,int m,struct c_comp *c);
int rpmul(double *a,int n,double *b,int m,double *c);
int cpdiv(struct c_comp *a,int n,struct c_comp *b,int m,struct c_comp *q,int k,struct c_comp *r,int l);
int rpdiv(double *a,int n,double *b,int m,double *q,int k,double *r,int l);
double rpva(double *a,int n,double x0);
int rpmva(double *a,int n,double *x,int m,double *y);
double rp2va(double *a,int m,int n,double x,double y);


//Chapter04
int c_minv(struct c_comp *mat,int n,double eps);
int c_matmul(struct c_comp *a, struct c_comp *b, int m, int p, int n, struct c_comp *c);


//Chapter05
int r_mqr(double *mat,int m,int n,double *q,double eps);
int toepl(double *t,double *b,double *x,int n,double eps);


//Chapter06


//Chapter07


//Chapter08
double lfsi(double a,double b,int n0,double eps,double(*f)(double));
double mont1(double a,double b,double(*f)(double));
double rbg(double a,double b,int n0,double eps,double(*f)(double));
double tzi2(double a,double b,int n0,double eps,double h0,double(*f)(double));


//Chapter09
int rungekuttainvh(double *y,int n,double(*f)(),double h,int m,double a);
int eulerinvh(double *y,int n,double(*f)(),double h,int m,double a);


//Chapter10


// Chapter11
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


//Chapter12
double brent(double a, double b, double c, double(*f)(double), double *xopt, double eps, int itmax);
void brake(double *a, double *b, double *c, double(*f)(double));
double dirmin(double *x, double *p, double *xmin, int n, double(*f)(), double eps, int itmax);
int bfgs(double *x, double *xmin, int n, double *y0, double(*f)(), void (*df)(), double eps, int itmax);


//Chapter13
double beta2(double a,double b,double x,double e1);


//Chapter14
#define STRU struct student
#define KEY age
//#define KEY name                                             /* 调用哈希函数需要的宏*/
#define NULLTag "\0"
#define DELTag "1\0"
#define HashSize 29
struct student                                               /* 定义存放学生信息的结构体*/
{
    int num;
    char name[8];
    char sex;
    int age;
};
typedef struct student ElemType;
typedef struct student* ElemTypeP;
typedef ElemType hashlist[HashSize];
typedef char KeyType[8];

int hashdel(hashlist HT,int m,ElemType a);
int hashins(hashlist HT,int m,ElemType a);
int hashsch(hashlist HT,int m,KeyType a);
int hashpos(char *str,int i,int m);
unsigned int hashk(char *str,int i);


//Chapter15



//Chapter16

int dct(double * x,int n, double *y);
int fft(struct c_comp *y,int n,struct c_comp *x);
int c_comp_plus(struct c_comp *a1,struct c_comp *a2,struct c_comp *c);
int c_comp_sub(struct c_comp *a1,struct c_comp *a2,struct c_comp *c);
int c_comp_product(struct c_comp *a1,struct c_comp *a2,struct c_comp *c);
int c_comp_divide(struct c_comp *a1,struct c_comp *a2,struct c_comp *c);
int c_comp_power(struct c_comp *a,struct c_comp *c,int n);
int c_comp_nthroot(struct c_comp *a,struct c_comp *c,int n);
int c_comp_exp(struct c_comp *a,struct c_comp *c);
int c_comp_log(struct c_comp *a,struct c_comp *c);
int c_comp_sin(struct c_comp *a,struct c_comp *c);
int c_comp_cos(struct c_comp *a,struct c_comp *c);


#endif // _UTILITY_H

