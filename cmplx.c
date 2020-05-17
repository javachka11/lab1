#include "cmplx.h"

void complexOutput(complex z) {
	printf("Result: (%lf; %lf)\n", z.re, z.im);
}

complex cmplx_sum(complex z1, complex z2) {
	complex res = { z1.re + z2.re, z1.im + z2.im };
	return res;
}

complex cmplx_prod(complex z1, complex z2) {
	complex res = { z1.re * z2.re - z1.im * z2.im, z1.re * z2.im + z1.im * z2.re };
	return res;
}
