#include "vector.h"
#include "cmplx.h"

void VectorOutput(Vector v) {
	if (v.arr == NULL)
		exit(1);
	printf("Dimension of Vector: %d\n", v.dim);
	printf("(");
	if (*((char*)v.arr - 1) == 'r') {
		for (int i = 0; i < v.dim; ++i) {
			printf("%lf", *((double*)v.arr + i));
			if (i < v.dim - 1)
				printf("; ");
		}
	}
	else if (*((char*)v.arr - 1) == 'c') {
		for (int i = 0; i < v.dim; ++i) {
			printf("[%lf; %lf]", *get_Re((complex*)v.arr + i), *get_Im((complex*)v.arr + i));
			if (i < v.dim - 1)
				printf("; ");
		}
	}
	printf(")\n");
}

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
	}
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
	}
	return res;
}


Vector VectorSumRealComplex(Vector v1, Vector v2) {
	Vector v;
	if ((char)(*((char*)v1.arr - 1) == 'r')) {
		v.dim = v2.dim;
		if ((v.arr = malloc(v.dim * sizeof(complex) + sizeof(char))) == NULL) {
			printf("ERROR: memory is not found!\n");
			v.dim = 0;
			return v;
		}
		*((char*)v.arr) = 'c';
		v.arr = (char*)v.arr + 1;
		for (int i = 0; i < v.dim; ++i) {
			*get_Re((complex*)v.arr + i) = (*((double*)v1.arr + i) + (*get_Re((complex*)v2.arr + i)));
			*get_Im((complex*)v.arr + i) = *get_Im((complex*)v2.arr + i);
		}
	} else {
		v.dim = v1.dim;
		printf("%d\n", v.dim);
		if ((v.arr = malloc(v.dim * sizeof(complex) + sizeof(char))) == NULL) {
			printf("ERROR: memory is not found!\n");
			v.dim = 0;
			return v;
		}
		*((char*)v.arr) = 'c';
		v.arr = (char*)v.arr + 1;
		for (int i = 0; i < v.dim; ++i) {
			*get_Re((complex*)v.arr + i) = (*((double*)v2.arr + i) + (*get_Re((complex*)v1.arr + i)));
			*get_Im((complex*)v.arr + i) = (*get_Im((complex*)v1.arr + i));
		}
	}
	return v;
}

Vector VectorSum(Vector v1, Vector v2) {
	Vector v;
	if ((char)(v1.arr == NULL) + (char)(v2.arr == NULL)) {
		printf("ERROR: v1 or v2 are NULL!\n");
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
	char r1 = (*((char*)v1.arr - 1) == 'r');
	char c1 = (*((char*)v1.arr - 1) == 'c');
	char r2 = (*((char*)v2.arr - 1) == 'r');
	char c2 = (*((char*)v2.arr - 1) == 'c');
	if (r1*c2 + r2*c1)
		return VectorSumRealComplex(v1, v2);
	else if (r1 * r2)
		return VectorSumReal(v1, v2);
	else if (c1 * c2)
		return VectorSumComplex(v1, v2);
	else {
		printf("Wrong type!\n");
		v.arr = NULL;
		v.dim = 0;
		return v;
	}
}


complex VectorScalarProductReal(Vector v1, Vector v2) {
	complex p = { 0, 0 };
	
	for (int i = 0; i < v1.dim; ++i) {
		p.re = p.re + (*((double*)v1.arr + i) * (*((double*)v2.arr + i)));
		p.im = 0;
	}
	return p;
}


complex VectorScalarProductComplex(Vector v1, Vector v2) {
	complex p = { 0.0, 0.0 };
	for (int i = 0; i < v1.dim; ++i) {
		p = cmplx_sum(p, cmplx_prod(*((complex*)v1.arr + i), *((complex*)v2.arr + i)));
	}
	return p;
}

complex VectorScalarProductRealComplex(Vector v1, Vector v2) {
	complex p = { 0.0, 0.0 };
	complex c = { 0.0, 0.0 };
	if ((char)(*((char*)v1.arr - 1) == 'r')) {
		for (int i = 0; i < v2.dim; ++i) {
			c.re = *get_Re((complex*)v2.arr + i) * (*((double*)v1.arr + i));
			c.im = *get_Im((complex*)v2.arr + i) * (*((double*)v1.arr + i));
			p = cmplx_sum(p, c);
		}
	} else {
		for (int i = 0; i < v2.dim; ++i) {
			c.re = *get_Re((complex*)v1.arr + i) * (*((double*)v2.arr + i));
			c.im = *get_Im((complex*)v1.arr + i) * (*((double*)v2.arr + i));
			p = cmplx_sum(p, c);
		}
	}
	return p;
}

complex VectorScalarProduct(Vector v1, Vector v2) {
	complex z;
	if ((char)(v1.arr == NULL) + (char)(v2.arr == NULL)) {
		printf("ERROR: v1 or v2 are NULL!");
		exit(1);
	}
	if (v1.dim != v2.dim) {
		printf("Different dimensions\n");
		exit(1);
	}
	char r1 = (*((char*)v1.arr - 1) == 'r');
	char c1 = (*((char*)v1.arr - 1) == 'c');
	char r2 = (*((char*)v2.arr - 1) == 'r');
	char c2 = (*((char*)v2.arr - 1) == 'c');
	if (r1 * c2 + r2 * c1)
		return VectorScalarProductRealComplex(v1, v2);
	else if (r1 * r2)
		return VectorScalarProductReal(v1, v2);
	else if (c1 * c2)
		return VectorScalarProductComplex(v1, v2);
	else {
		printf("Wrong type!\n");
		exit(1);
	}
}

void FreeVector(Vector v) {
	if (v.arr != NULL)
		free((char*)v.arr - 1);
}