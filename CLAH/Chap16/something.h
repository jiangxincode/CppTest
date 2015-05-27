#ifndef _SOMETHING_H
#define _SOMETHING_H

struct c_comp{
    double rmz;
    double imz;
}c_comp;

#define PI 3.1415926

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
#endif // _SOMETHING_H

