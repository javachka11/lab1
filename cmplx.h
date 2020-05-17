#pragma once
typedef struct complex {
	double re;
	double im;
} complex;
#define get_Re(Z)  (&((Z)->re))
#define get_Im(Z)  (&((Z)->im))

void complexOutput(complex);
complex cmplx_sum(complex, complex);
complex cmplx_prod(complex, complex);