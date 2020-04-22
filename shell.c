#include "vector.h"
#include "cmplx.h"



Vector VectorCreateReal() {
	Vector v;
	printf("Input dimension: ");
	scanf("%d", &v.dim);
	if ((v.arr = malloc(v.dim * sizeof(double) + sizeof(char))) == NULL) {
		printf("ERROR: memory is not found!\n");
		v.dim = 0;
		return v;
	}
	*((char*)v.arr) = 'r';
	v.arr = (char*)v.arr + 1;
	for (int i = 0; i < v.dim; ++i) {
		printf("Input element %d: ", i + 1);
		scanf("%lf", (double*)v.arr + i);
	}
	return v;
}

Vector VectorCreateComplex() {
	Vector v;
	printf("Input dimension: ");
	scanf("%d", &v.dim);
	if ((v.arr = malloc(v.dim * sizeof(complex) + sizeof(char))) == NULL) {
		printf("ERROR: memory is not found!\n");
		v.dim = 0;
		return v;
	}
	*((char*)v.arr) = 'c';
	v.arr = (char*)v.arr + 1;
	for (int i = 0; i < v.dim; ++i) {
		printf("Input re-element %d: ", i + 1);
		scanf("%lf", get_Re((complex*)v.arr + i));
		printf("Input im-element %d: ", i + 1);
		scanf("%lf", get_Im((complex*)v.arr + i));
	}
	return v;
}

Vector VectorCreate() {
	static char i = 1;
	printf("%d vector: which type of elements do you choose? r/c\n", i);
	++i;
	char c;
	if (i == 3)
		getchar();
	c = getchar();
	printf("%d", c);
	if ((char)(c == 'r'))
		return VectorCreateReal();
	else if ((char)(c == 'c'))
		return VectorCreateComplex();
	else {
		printf("You input wrong symbol!\n");
	    Vector v = { NULL, 0 };
	    return v;
	}
}
Vector VectorSumReal(Vector v1, Vector v2) {
	Vector res;
	res.dim = v1.dim;
	if ((res.arr = malloc(res.dim * sizeof(double) + sizeof(char))) == NULL) {
		printf("ERROR: memory is not found!\n");
		res.dim = 0;
		return res;
	}
	*((char*)res.arr) = 'r';
	res.arr = (char*)res.arr + 1;
	for (int i = 0; i < res.dim; ++i) {
		*((double*)res.arr + i) = *((double*)v1.arr + i) + *((double*)v2.arr + i);
		printf("%lf ", *((double*)res.arr + i));
	}
	printf("\n");
	return res;
}

Vector VectorSumComplex(Vector v1, Vector v2) {
	Vector res;
	res.dim = v1.dim;
	if ((res.arr = malloc(res.dim * sizeof(complex) + sizeof(char))) == NULL) {
		printf("ERROR: memory is not found!\n");
		res.dim = 0;
		return res;
	}
	*((char*)res.arr) = 'c';
	res.arr = (char*)res.arr + 1;
	for (int i = 0; i < res.dim; ++i) {
		*((complex*)res.arr + i) = cmplx_sum(*((complex*)v1.arr + i), *((complex*)v2.arr + i));
		printf("(%lf %lf) ", *get_Re((complex*)res.arr + i), *get_Im((complex*)res.arr + i));
	}
	printf("\n");
	return res;
}

Vector VectorSum(Vector v1, Vector v2) {
	Vector v;
	if ((char)(v1.arr == NULL) + (char)(v2.arr == NULL)) {
		v.arr = NULL;
		v.dim = 0;
		return v;
	}
	if (*((char*)v1.arr - 1) != *((char*)v2.arr - 1)) {
		printf("Different types of elements\n");
		v.arr = NULL;
		v.dim = 0;
		return v;
	}
	if (v1.dim != v2.dim) {
		printf("Different dimensions\n");
		v.arr = NULL;
		v.dim = 0;
		return v;
	}
	if (*((char*)v1.arr - 1) == 'r')
		return VectorSumReal(v1, v2);
	else if (*((char*)v1.arr - 1) == 'c')
		return VectorSumComplex(v1, v2);
	else {
		printf("Wrong type!\n");
		v.arr = NULL;
		v.dim = 0;
		return v;
	}
}



double* VectorScalarProductReal(Vector v1, Vector v2) {
	double p = 0.0;
	
	for (int i = 0; i < v1.dim; ++i) {
		p += *((double*)v1.arr + i) * (*((double*)v2.arr + i));
	}
	printf("%lf\n", p);
	return &p;
}


complex* VectorScalarProductComplex(Vector v1, Vector v2) {
	complex p = { 0.0, 0.0 };
	for (int i = 0; i < v1.dim; ++i) {
		p = cmplx_sum(p, cmplx_prod(*((complex*)v1.arr + i), *((complex*)v2.arr + i)));
	}
	printf("(%lf %lf)\n", p.re, p.im);
	return &p;
}

void* VectorScalarProduct(Vector v1, Vector v2) {
	if ((char)(v1.arr == NULL) + (char)(v2.arr == NULL)) {
		return NULL;
	}
	if (*((char*)v1.arr - 1) != *((char*)v2.arr - 1)) {
		printf("Different types of elements\n");
		return NULL;
	}
	if (v1.dim != v2.dim) {
		printf("Different dimensions\n");
		return NULL;
	}

	if (*((char*)v1.arr - 1) == 'r')
		return VectorScalarProductReal(v1, v2);
	else if (*((char*)v1.arr - 1) == 'c')
		return VectorScalarProductComplex(v1, v2);
	else {
		printf("Wrong type!\n");
		return NULL;
	}
}

void FreeVector(Vector v) {
	if (v.arr != NULL)
		free((char*)v.arr - 1);
}