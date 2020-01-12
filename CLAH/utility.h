#ifndef _UTILITY_H
#define _UTILITY_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define PI 3.1415926
#define EPS 1.0e-6


/* Chapter02 */
struct c_comp
{
    double rmz; /* real part */
    double imz; /* imaginary part */
} c_comp;

int c_comp_plus(const struct c_comp *a1,const struct c_comp *a2,struct c_comp *c);
int c_comp_sub(const struct c_comp *a1,const struct c_comp *a2,struct c_comp *c);
int c_comp_product(const struct c_comp *a1,const struct c_comp *a2,struct c_comp *c);
int c_comp_divide(const struct c_comp *a1,const struct c_comp *a2,struct c_comp *c);
int c_comp_power(const struct c_comp *a,struct c_comp *c,const int n);
int c_comp_nthroot(const struct c_comp *a,struct c_comp *c,const int n);
int c_comp_exp(const struct c_comp *a,struct c_comp *c);
int c_comp_log(const struct c_comp *a,struct c_comp *c);
int c_comp_sin(const struct c_comp *a,struct c_comp *c);
int c_comp_cos(const struct c_comp *a,struct c_comp *c);


/* Chapter03 */
int c2p(struct c_comp *a,int n,struct c_comp *y);
int p2c(struct c_comp *y,int n,struct c_comp *a);
int cpmul(struct c_comp *a,int n,struct c_comp *b,int m,struct c_comp *c);
int rpmul(double *a,int n,double *b,int m,double *c);
int cpdiv(struct c_comp *a,int n,struct c_comp *b,int m,struct c_comp *q,int k,struct c_comp *r,int l);
int rpdiv(double *a,int n,double *b,int m,double *q,int k,double *r,int l);
double rpva(double *a,int n,double x0);
int rpmva(double *a,int n,double *x,int m,double *y);
double rp2va(double *a,int m,int n,double x,double y);


/* Chapter04 */
int c_minv(struct c_comp *mat,int n,double eps);
int c_matmul(struct c_comp *a, struct c_comp *b, int m, int p, int n, struct c_comp *c);
int jcb1(double *a,int n,double *u,double eps,int itmax);
int jcb2(double *a,int n,double *u,double eps,int itmax);
int r_matmul(double *a, double *b, int m, int p, int n, double *c);
int mhdqr(double *a,int n,double *u,double *v,double eps,int itmax);
int sdminv(double *mat, int n, double eps);
int smtr(double *mat,int n,double *q,double eps);
int r_mlu(double *mat,int n,double *L,double *U,double *P,double *Q,double eps);
int r_mrank(double *mat,int m, int n,double eps);
double r_mdet(double *mat, int n, double eps);
double r_chdet(double *mat,int n,double eps);
int smdqr(double *a,int n,double *u,double eps,int itmax);
int Tminv(double *t1,double *t2,int n,double *mat,double eps);
int smldl(double *mat,int n,double *L,double *D,double eps);
int mhhbg(double *mat,int n,double *q,double eps);


/* Chapter05 */
int r_mqr(double *mat,int m,int n,double *q,double eps);
int toepl(double *t,double *b,double *x,int n,double eps);
int r_chol(double *mat,int n,double *u,double eps);
int bmqr(double *a,double *b,double *x,int n,double eps,int iter);
int c_gaus(struct c_comp *a,struct c_comp *b,struct c_comp *x,int n,double eps);
int c_gsjd(struct c_comp *a,struct c_comp *b,struct c_comp *x,int n,double eps);
int r_ldl(double *a,double *b,double *x,int n,double eps);
int r_chde(double *a,double *b,double *x,int n,double eps);
int gmqr(double *a,double *b,double *x,int m,int n,double eps);
int jaco(double *a,double *b,double *x,int n,double eps,int iter);
int gssd(double *a,double *b,double *x,int n,double eps,int iter);
int orelax(double *a,double *b,double *x,int n,double w,double eps,int iter);
int smcg(double *a,double *b,double *x,int n,double eps,int iter);
int b_gsjd(double *a,double *b,double *x,int n,double eps);
int r_trzg(double *a,double *b,double *x,int n,double eps);
int r_gsband(double *a,double *b,double *x,int n,int h,double eps);
int r_gsjd(double *a,double *b,double *x,int n,double eps);
int r_gaus(double *a,double *b,double *x,int n,double eps);


/* Chapter06 */
int interroot(double *x0,double ab,double(*f)(),double eps,int max);
int newdonroot(double *x0,double(*f)(),double(*fd)(),double eps,int max);
int qrroot(double *a,int n,double *u,double *v,double eps,int itmax);
int aitkenroot(double *x0,double(*f)(),double eps,int max);
double disroot(double a,double b,double (*f)(),double eps);
int gradroot(double *x0,int n,double (*f)(),double eps,int max);
int nndroot(double *x0,int n,void (*f)(),double eps,int max,double h,double t);


/* Chapter07 */
double lagr7(double *x,double *y,int n,double t);
double atken(double *x,double *y,int n,double t,double eps);
double atkene(double x,double h,double *y,int n,double t,double eps);
int bspl1(double *x,double *y,double y1,double y2,int n,double *t,int m,double *z,double *z1,double *z2);
int bspl2(double *x,double *y,double y1,double y2,int n,double *t,int m,double *z,double *z1,double *z2);
int bspl3(double *x,double *y,int n,double *t,int m,double *z,double *z1,double *z2);
double hmt(double *x,double *y,double *dy,int n,double t);
double hmte(double x,double h,double *y,double *dy,int n,double t);
double lagr1(double *x,double *y,int n,double t);
double lagr2(double *x,double *y,int n,double t);
double spl(double *x,double *y,int n,double t,double eps);
double sple(double x,double h,double *y,int n,double t,double eps);
double lfs(double *x,double *y,int n,double t,double eps);


/* Chapter08 */
double lfsi(double a,double b,int n0,double eps,double(*f)(double));
double mont1(double a,double b,double(*f)(double));
double mont2(double x0,double x1,double y0,double y1,double(*f)());
double rbg(double a,double b,int n0,double eps,double(*f)(double));
double tzi2(double a,double b,int n0,double eps,double h0,double(*f)(double));
double tzi1(double a,double b,int n0,double eps,double h0,double(*f)(double));
double cheb(double a,double b,int n0,double eps,double h0,double(*f)());
double gasi(double a,double b,double eps,int nmax,double(*f)());
double lagr(double a,double (*f)(),int p);
double hemt(double(*f)());
double simps1(double a,double b,int n0,double eps,double h0,double(*f)(double));
double simps2(double a,double b,int n0,double eps,double h0,double(*f)(),void (*fy)());
double lfsi2(double a,double b,int n0,double eps,double(*f)(),void (*fy)());
double leg1(double a,double b,int n0,double eps,double h0,double(*f)());


/* Chapter09 */
int rungekuttainvh(double *y,int n,double(*f)(),double h,int m,double a);
int eulerinvh(double *y,int n,double(*f)(),double h,int m,double a);
int eulervh(double *y,int n,double(*f)(),double h,int m,double a,double eps);
int bb(double *y,int n,double(*f)(),double h,int m,double a);
int euleradv(double *y,int n,double(*f)(),double h,int m,double a);
int adams(double *y,int n,double(*f)(),double h,int m,double a);
int hamming(double *y,int n,double (*f)(),double h,int m,double a);
int rungekuttavh(double *y,int n,double (*f)(),double h,int m,double a,double eps);
int gillvh(double *y,int n,double (*f)(),double h,int m,double a,double eps);


/* Chapter10 */
int lsq(double *x,double *y,int n,double *p,int pp,double *s);
int lsq2(double *x,double *y,double *z,int n,int m,double *p,int pp,int qq,double *s);


/* Chapter11 */
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

double J0(double);
double J1(double);
double I0(double x);
double I1(double x);
double K0(double x);
double K1(double x);
double Y0(double x);
double Y1(double x);


/* Chapter12 */
double brent(double a, double b, double c, double(*f)(double), double *xopt, double eps, int itmax);
void brake(double *a, double *b, double *c, double(*f)(double));
double dirmin(double *x, double *p, double *xmin, int n, double(*f)(), double eps, int itmax);
int bfgs(double *x, double *xmin, int n, double *y0, double(*f)(), void (*df)(), double eps, int itmax);
int cggm1(double *x, double *xmin, int n, double *y0, double(*f)(), void (*df)(), double eps, int itmax);
int cggm2(double *x, double *xmin, int n, double *y0, double(*f)(), void (*df)(), double eps, int itmax);
double dbrent(double a, double b, double c, double(*f)(double),double(*df)(double), double *xopt, double eps, int itmax);
double ddirmin(double *x, double *p, double *xmin, int n, double (*f)(double),double (*df)(double), double eps, int itmax);
double goldsch(double a, double b, double c, double(*f)(double), double *xopt, double eps);
int powell(double *x, double *ee, double *xmin, int n, double *y0, double(*f)(), double eps, int itmax);
int simp1(double d,int n,double lam,double alf,double miu,double *x,double *fx,double *xopt,double(*f)(),double eps,int itmax);
int simp2(int n,int m,double *a,double *b,double d,double alf,double eps,double *x,double *fx,double *xopt,int (*sf)(),double(*f)(),int itmax);
int simplex(double *a,int n,int m1,int m2,int m3,int *ixr,int *ixc,double eps);


/* Chapter13 */
int c2test(int *a,int *e,int r,int k,int *v,double *c2,double alpha);
int ftest(double *a,int na,double *b,int nb,double alpha);
void mde(double *a,int n,double *mean,double *adev,double *sddev,double *var,double *skew,double *kurt);
double randgsab(double a,double b);
double randgsabs(int L,double a,double b,double *G);
int randu01s(int L,double *u_ran);
int randuabs(int L,int a,int b,int * uab_ran);
int ttest(double *a,int na,double *b,int nb,double alpha);
int tutest(double *a,int na,double *b,int nb,double alpha);


/* Chapter14 */
#define STRU (struct student)
#define KEY age /* 调用哈希函数需要的宏*/
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

int hashdel(struct student HT[HashSize],int m,struct student a);
int hashins(struct student HT[HashSize],int m,struct student a);
int hashsch(struct student HT[HashSize],int m,char a[8]);
int hashpos(char *str,int i,int m);
unsigned int hashk(char *str,int i);
int bist(int *x,int n,int a);
int Fsech(FILE *fp,int a,struct student *str);
void mima(int *x,int n,int *mi,int *ma);
void mmas(int *x,int n,int m);
void qcks(int *x,int s,int t);
int sech(struct student *x,int n,int k,int a);
int	KeyEqu(char* stra,char* strb);   /* 判断关键字是否相同*/
void ElemCP(struct student *a, struct student *b);                         /* 将元素b中内容拷贝到a中*/
void ElemDEL(struct student *a);                                    /* 将元素a设成已删除*/
void ElemNULL(struct student *a);                                   /* 将元素a设成空，用于初始化或清空哈希表*/


/* Chapter15 */
void cout(int *x,int *y,int n,int k);
void heap(int *x,int n);
void inst(int *x,int n);
void mgst(int *x,int n);
void popo(int *x,int n);
void rads(int *x,int n,int d,int k);
void selt(int *x,int n);
void shel(int *x,int n);


/* Chapter16 */
int dct(double * x,int n, double *y);
int fft(struct c_comp *y,int n,struct c_comp *x);
int wolt(double *y,int n,double *x);
int r2fft(double *x1,double *x2,int n,struct c_comp *y1,struct c_comp *y2);
int ifft(struct c_comp *y,int n,struct c_comp *x);
int kabg(double *x,int n,double *y,double h,double alfa,double beta,double gama);
int smoth(double *x,int n,double *y);
int hadma(double *y,int n,double *x);

#endif // _UTILITY_H

