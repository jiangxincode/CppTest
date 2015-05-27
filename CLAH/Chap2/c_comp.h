#ifndef C_COMP_H
#define C_COMP_H

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

#endif
