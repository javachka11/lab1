#include "cmplx.h"

double* get_Re(complex* z) {
	return &z->re;
}

double* get_Im(complex* z) {
	return &z->im;
}

complex cmplx_sum(complex z1, complex z2) {
	complex res = { z1.re + z2.re, z1.im + z2.im };
	return res;
}

complex cmplx_prod(complex z1, complex z2) {
	complex res = { z1.re * z2.re - z1.im * z2.im, z1.re * z2.im + z1.im * z2.re };
	return res;
}
