double brent(double a, double b, double c, double (*f)(double), double *xopt, double eps, int itmax);
void brake(double *a, double *b, double *c, double (*f)(double));
double dirmin(double *x, double *p, double *xmin, int n, double (*f)(), double eps, int itmax);
int bfgs(double *x, double *xmin, int n, double *y0, double (*f)(), void (*df)(), double eps, int itmax);
