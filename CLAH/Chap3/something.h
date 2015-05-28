#ifndef _CHAP3_SOMETHING_H_
#define _CHAP3_SOMETHING_H_

#include "../Chap2/c_comp.h"

int c2p(struct c_comp *a,int n,struct c_comp *y);
int p2c(struct c_comp *y,int n,struct c_comp *a);
int cpmul(struct c_comp *a,int n,struct c_comp *b,int m,struct c_comp *c);
int rpmul(double *a,int n,double *b,int m,double *c);
int cpdiv(struct c_comp *a,int n,struct c_comp *b,int m,struct c_comp *q,int k,struct c_comp *r,int l);
int rpdiv(double *a,int n,double *b,int m,double *q,int k,double *r,int l);
double rpva(double *a,int n,double x0);
int rpmva(double *a,int n,double *x,int m,double *y);
double rp2va(double *a,int m,int n,double x,double y);

#endif // _CHAP3_SOMETHING_H_
