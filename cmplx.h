#pragma once
typedef struct complex {
	double re;
	double im;
} complex;

double* get_Re(complex*);
double* get_Im(complex*);
complex cmplx_sum(complex, complex);
complex cmplx_prod(complex, complex);