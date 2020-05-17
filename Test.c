#include "shell.h"
#define EPS 1e-8

double VAbs(double x) {
	if (x >= 0)
		return x;
	else
		return -x;
}


Vector test_realVector(double* a, int n) {
	Vector v;
	v.dim = n;
	if ((v.arr = malloc(v.dim * sizeof(double) + sizeof(char))) == NULL) {
		printf("ERROR: memory is not found!\n");
		v.dim = 0;
		return v;
	}
	*((char*)v.arr) = 'r';
	(char*)v.arr = (char*)v.arr + 1;
	for (char i = 0; i < n; ++i) {
		*((double*)v.arr + i) = *(a + i);
	}
	return v;
}

Vector test_complexVector(double* a, int n) {
	Vector v;
	v.dim = n;
	if ((v.arr = malloc(v.dim * sizeof(complex) + sizeof(char))) == NULL) {
		printf("ERROR: memory is not found!\n");
		v.dim = 0;
		return v;
	}
	*((char*)v.arr) = 'c';
	(char*)v.arr = (char*)v.arr + 1;
	for (char i = 0; i < n; ++i) {
		*(get_Re((complex*)v.arr + i)) = *(a + 2*i);
		*(get_Im((complex*)v.arr + i)) = *(a + 2*i + 1);
	}
	return v;
}

void sumrealtest() {
	Vector v1, v2, v_sum;
	char f = 0;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 , 8.0 };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 , 3.01 };
	double test_c[] = { 7.4 , 7.9 , 7.07 , 6.15, 11.01 };
	v1 = test_realVector(test_a, 5);
	v2 = test_realVector(test_b, 5);
	v_sum = VectorSum(v1, v2);
	if ((char)(v_sum.arr == NULL))
		return;
	for (char i = 0; i < 5; ++i) {
		if ((char)(VAbs(*((double*)v_sum.arr + i) - test_c[i]) < EPS))
			++f;
	}
	if (f == 5)
		printf("Test of \"sumrealtest\" completed!\n");
	else
		printf("ERROR: sumrealtest\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum);

}

void sumrealtest_zero() {
	Vector v1, v2, v_sum;
	char f = 0;
	double test_a[] = { 4.2, 1.5, 3.77, 4.4, 8.0 };
	double test_b[] = { 0, 0, 0, 0, 0 };
	double test_c[] = { 4.2, 1.5, 3.77, 4.4, 8.0 };
	v1 = test_realVector(test_a, 5);
	v2 = test_realVector(test_b, 5);
	v_sum = VectorSum(v1, v2); 
	if ((char)(v_sum.arr == NULL))
		return;
	for (char i = 0; i < 5; ++i) {
		if ((char)(VAbs(*((double*)v_sum.arr + i) - test_c[i]) < EPS))
			++f;
	}
	if (f == 5)
		printf("Test of \"sumrealtest_zero\" completed!\n");
	else
		printf("ERROR: sumrealtest_zero\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum);
}

void sumrealtest_minus() {
	Vector v1, v2, v_sum;
	char f = 0;
	double test_a[] = { 4.2, 1.5, 3.77, 4.4, 8.0 };
	double test_b[] = { -4.2, -1.5, -3.77, -4.4, -8.0 };
	v1 = test_realVector(test_a, 5);
	v2 = test_realVector(test_b, 5);
	v_sum = VectorSum(v1, v2);
	if ((char)(v_sum.arr == NULL))
		return;
	for (char i = 0; i < 5; ++i) {
		if ((char)(VAbs(*((double*)v_sum.arr + i) - 0.0) < EPS))
			++f;
	}
	if (f == 5)
		printf("Test of \"sumrealtest_minus\" completed!\n");
	else
		printf("ERROR: sumrealtest_minus\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum);
}

void sumrealtest_commut() {
	Vector v1, v2, v_sum1, v_sum2;
	char f = 0;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 , 8.0 };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 , 3.01 };
	v1 = test_realVector(test_a, 5);
	v2 = test_realVector(test_b, 5);
	v_sum1 = VectorSum(v1, v2);
	v_sum2 = VectorSum(v2, v1);
	if ((char)(v_sum1.arr == NULL) + (char)(v_sum2.arr == NULL))
		return;
	for (char i = 0; i < 5; ++i) {
		if ((char)(VAbs(*((double*)v_sum1.arr + i) - *((double*)v_sum2.arr + i)) < EPS))
			++f;
	}
	if (f == 5)
		printf("Test of \"sumrealtest_commut\" completed!\n");
	else
		printf("ERROR: sumrealtest_commut\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum1);
	FreeVector(v_sum2);

}

void sumrealtest_assoc() {
	Vector v1, v2, v3, v1_sum12, v1_sum, v2_sum23, v2_sum;
	char f = 0;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 , 8.0 };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 , 3.01 };
	double test_c[] = { 2.1, 3.33, 0.1, 2.222, 1.4, 1.4 };
	v1 = test_realVector(test_a, 5);
	v2 = test_realVector(test_b, 5);
	v3 = test_realVector(test_c, 5);
	v1_sum12 = VectorSum(v1, v2);
	v1_sum = VectorSum(v1_sum12, v3);
	v2_sum23 = VectorSum(v2, v3);
	v2_sum = VectorSum(v1, v2_sum23);
	if ((char)(v1_sum.arr == NULL) + (char)(v2_sum.arr == NULL))
		return;
	for (char i = 0; i < 5; ++i) {
		if ((char)(VAbs(*((double*)v1_sum.arr + i) - *((double*)v2_sum.arr + i)) < EPS))
			++f;
	}
	if (f == 5)
		printf("Test of \"sumrealtest_assoc\" completed!\n");
	else
		printf("ERROR: sumrealtest_assoc\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v3);
	FreeVector(v1_sum12);
	FreeVector(v1_sum);
	FreeVector(v2_sum23);
	FreeVector(v2_sum);



}


void sumrealtest_num() {
	Vector v1, v2, v_sum;
	double test_a[] = { 4.2 };
	double test_b[] = { 3.21 };
	v1 = test_realVector(test_a, 1);
	v2 = test_realVector(test_b, 1);
	v_sum = VectorSum(v1, v2);
	if ((char)(v_sum.arr == NULL))
		return;
	if ((char)(VAbs(*((double*)v_sum.arr) - 7.41) < EPS))
		printf("Test of \"sumrealtest_num\" completed!\n");
	else
		printf("ERROR: sumrealtest_num\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum);
}



void sumcomplextest() {
	Vector v1, v2, v_sum;
	char f = 0;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 };
	double test_c[] = { 7.4 , 7.9 , 7.07 , 6.15 };
	v1 = test_complexVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	v_sum = VectorSum(v1, v2);
	if ((char)(v_sum.arr == NULL))
		return;
	char b;
	for (char i = 0; i < 2; ++i) {
		b = (char)(VAbs(*(get_Re((complex*)v_sum.arr + i)) - test_c[2*i]) < EPS);
		b *= (char)(VAbs(*(get_Im((complex*)v_sum.arr + i)) - test_c[2*i + 1]) < EPS);
		if (b) ++f;
	}
	if (f == 2)
		printf("Test of \"sumcomplextest\" completed!\n");
	else
		printf("ERROR: sumcomplextest\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum);
}

void sumcomplextest_zero() {
	Vector v1, v2, v_sum;
	char f = 0;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 };
	double test_b[] = { 0 , 0 , 0 , 0 };
	v1 = test_complexVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	v_sum = VectorSum(v1, v2);
	if ((char)(v_sum.arr == NULL))
		return;
	char b;
	for (char i = 0; i < 2; ++i) {
		b = (char)(VAbs(*(get_Re((complex*)v_sum.arr + i)) - test_a[2 * i]) < EPS);
		b *= (char)(VAbs(*(get_Im((complex*)v_sum.arr + i)) - test_a[2 * i + 1]) < EPS);
		if (b) ++f;
	}
	if (f == 2)
		printf("Test of \"sumcomplextest_zero\" completed!\n");
	else
		printf("ERROR: sumcomplextest_zero\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum);
}

void sumcomplextest_minus() {
	Vector v1, v2, v_sum;
	char f = 0;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 };
	double test_b[] = { -4.2 , -1.5 , -3.77 , -4.4 };
	v1 = test_complexVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	v_sum = VectorSum(v1, v2);
	if ((char)(v_sum.arr == NULL))
		return;
	char b;
	for (char i = 0; i < 2; ++i) {
		b = (char)(VAbs(*(get_Re((complex*)v_sum.arr + i)) - 0.0) < EPS);
		b *= (char)(VAbs(*(get_Im((complex*)v_sum.arr + i)) - 0.0) < EPS);
		if (b) ++f;
	}
	if (f == 2)
		printf("Test of \"sumcomplextest_minus\" completed!\n");
	else
		printf("ERROR: sumcomplextest_minus\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum);
}


void sumcomplextest_commut() {
	Vector v1, v2, v_sum1, v_sum2;
	char f = 0;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 };
	v1 = test_complexVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	v_sum1 = VectorSum(v1, v2);
	v_sum2 = VectorSum(v2, v1);
	if ((char)(v_sum1.arr == NULL) + (char)(v_sum2.arr == NULL))
		return;
	char b;
	for (char i = 0; i < 2; ++i) {
		b = (char)(VAbs(*(get_Re((complex*)v_sum1.arr + i)) - *(get_Re((complex*)v_sum2.arr + i))) < EPS);
		b *= (char)(VAbs(*(get_Im((complex*)v_sum1.arr + i)) - *(get_Im((complex*)v_sum2.arr + i))) < EPS);
		if (b) ++f;
	}
	if (f == 2)
		printf("Test of \"sumcomplextest_commut\" completed!\n");
	else
		printf("ERROR: sumcomplextest_commut\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum1);
	FreeVector(v_sum2);

}

void sumcomplextest_assoc() {
	Vector v1, v2, v3, v1_sum12, v1_sum, v2_sum23, v2_sum;
	char f = 0;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4  };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 };
	double test_c[] = { 2.1, 3.33, 0.1, 2.222 };
	v1 = test_complexVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	v3 = test_complexVector(test_c, 2);
	v1_sum12 = VectorSum(v1, v2);
	v1_sum = VectorSum(v1_sum12, v3);
	v2_sum23 = VectorSum(v2, v3);
	v2_sum = VectorSum(v1, v2_sum23);
	if ((char)(v1_sum.arr == NULL) + (char)(v2_sum.arr == NULL))
		return;
	char b;
	for (char i = 0; i < 2; ++i) {
		b = (char)(VAbs(*(get_Re((complex*)v1_sum.arr + i)) - *(get_Re((complex*)v2_sum.arr + i))) < EPS);
		b *= (char)(VAbs(*(get_Im((complex*)v1_sum.arr + i)) - *(get_Im((complex*)v2_sum.arr + i))) < EPS);
		if (b) ++f;
	}
	if (f == 2)
		printf("Test of \"sumcomplextest_assoc\" completed!\n");
	else
		printf("ERROR: sumcomplextest_assoc\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v3);
	FreeVector(v1_sum12);
	FreeVector(v1_sum);
	FreeVector(v2_sum23);
	FreeVector(v2_sum);
}


void sumtest_diftypes() {
	Vector v1, v2, v_sum;
	char f = 0;
	double test_a[] = { 4.2, 1.5 };
	double test_b[] = { 2.3, 3.2, 3.77, 4.4 };
	double test_c[] = { 6.5, 3.2, 5.27, 4.4 };
	v1 = test_realVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	v_sum = VectorSum(v1, v2);
	if ((char)(v_sum.arr == NULL))
		return;
	char b;
	for (char i = 0; i < 2; ++i) {
		b = (char)(VAbs(*(get_Re((complex*)v_sum.arr + i)) - test_c[2 * i]) < EPS);
		b *= (char)(VAbs(*(get_Im((complex*)v_sum.arr + i)) - test_c[2 * i + 1]) < EPS);
		if (b) ++f;
	}
	if (f == 2)
		printf("Test of \"sumtest_diftypes\" completed!\n");
	else
		printf("ERROR: sumtest_diftypes\n");
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum);
}

void sumtest_difdims() {
	Vector v1, v2, v_sum;
	char f = 0;
	double test_a[] = { 4.2, 1.5, 3.77, 4.4, 8.0 };
	double test_b[] = { 2.1, 3.4, 3.2, 1.1 };
	v1 = test_realVector(test_a, 5);
	v2 = test_realVector(test_b, 4);
	v_sum = VectorSum(v1, v2);
	if ((char)(v_sum.arr == NULL))
		printf("Test of \"sumtest_difdims\" completed!\n");
	else
		printf("ERROR: sumtest_difdims\n");
	FreeVector(v1);
	FreeVector(v2);
}




void scprodrealtest() {
	Vector v1, v2;
	complex z;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 , 8.0 };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 , 3.01 };
	v1 = test_realVector(test_a, 5);
	v2 = test_realVector(test_b, 5);
	z = VectorScalarProduct(v1, v2);
	if ((char)(VAbs(z.re - 67.261) < EPS) * (char)(VAbs(z.im - 0.0) < EPS))
		printf("Test of \"scprodtestreal\" completed!\n");
	else
		printf("ERROR: scprodtestreal\n");
	FreeVector(v1);
	FreeVector(v2);
}

void scprodrealtest_zero() {
	Vector v1, v2;
	complex z;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 , 8.0 };
	double test_b[] = { 0, 0, 0, 0, 0 };
	v1 = test_realVector(test_a, 5);
	v2 = test_realVector(test_b, 5);
	z = VectorScalarProduct(v1, v2);
	if ((char)(VAbs(z.re - 0.0) < EPS) * (char)(VAbs(z.im - 0.0) < EPS))
		printf("Test of \"scprodtestreal_zero\" completed!\n");
	else
		printf("ERROR: scprodtestreal_zero\n");
	FreeVector(v1);
	FreeVector(v2);
}

void scprodrealtest_commut() {
	Vector v1, v2;
	complex a;
	complex b;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 , 8.0 };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 , 3.01 };
	v1 = test_realVector(test_a, 5);
	v2 = test_realVector(test_b, 5);
	a = VectorScalarProduct(v1, v2);
	b = VectorScalarProduct(v2, v1);
	if ((char)(VAbs(a.re - b.re) < EPS) * (char)(VAbs(a.im - b.im) < EPS))
		printf("Test of \"scprodtestreal_commut\" completed!\n");
	else
		printf("ERROR: scprodtestreal_commut\n");
	FreeVector(v1);
	FreeVector(v2);
}

void scprodrealtest_num() {
	Vector v1, v2;
	complex z;
	double test_a[] = { 4.2 };
	double test_b[] = { 3.2 };
	
	v1 = test_realVector(test_a, 1);
	v2 = test_realVector(test_b, 1);
	z = VectorScalarProduct(v1, v2);
	if ((char)(VAbs(z.re - 13.44) < EPS) * (char)(VAbs(z.im - 0.0) < EPS))
		printf("Test of \"scprodtestreal_num\" completed!\n");
	else
		printf("ERROR: scprodtestreal_num\n");
	FreeVector(v1);
	FreeVector(v2);
}

void scprodcomplextest() {
	Vector v1, v2;
	complex z;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 };
	v1 = test_complexVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	z = VectorScalarProduct(v1, v2);
	if ((char)(VAbs(z.re - 8.581) < EPS) * (char)(VAbs(z.im - 52.7975) < EPS))
		printf("Test of \"scprodtestcomplex\" completed!\n");
	else
		printf("ERROR: scprodtestcomplex\n");
	FreeVector(v1);
	FreeVector(v2);
}
 
void scprodcomplextest_zero() {
	Vector v1, v2;
	complex z;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 };
	double test_b[] = { 0 , 0 , 0 , 0 };
	v1 = test_complexVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	z = VectorScalarProduct(v1, v2);
	if ((char)(VAbs(z.re - 0.0) < EPS) * (char)(VAbs(z.im - 0.0) < EPS))
		printf("Test of \"scprodtestcomplex_zero\" completed!\n");
	else
		printf("ERROR: scprodtestcomplex_zero\n");
	FreeVector(v1);
	FreeVector(v2);
}

void scprodcomplextest_commut() {
	Vector v1, v2;
	complex a;
	complex b;
	double test_a[] = { 4.2 , 1.5 , 3.77 , 4.4 };
	double test_b[] = { 3.2 , 6.4 , 3.3 , 1.75 };
	v1 = test_complexVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	a = VectorScalarProduct(v1, v2);
	b = VectorScalarProduct(v2, v1);
	if ((char)(VAbs(a.re - b.re) < EPS) * (char)(VAbs(a.im - b.im) < EPS))
		printf("Test of \"scprodtestcomplex_commut\" completed!\n");
	else
		printf("ERROR: scprodtestcomplex_commut\n");
	FreeVector(v1);
	FreeVector(v2);
}

void scprodtest_diftypes() {
	Vector v1, v2;
	complex z;
	double test_a[] = { 4.2, 1.5 };
	double test_b[] = { 2.3, 3.2, 3.77, 4.4 };
	v1 = test_realVector(test_a, 2);
	v2 = test_complexVector(test_b, 2);
	z = VectorScalarProduct(v1, v2);
	if ((char)(VAbs(z.re - 15.315) < EPS) * (char)(VAbs(z.im - 20.04) < EPS))
		printf("Test of \"scprodtest_diftypes\" completed!\n");
	else
		printf("ERROR: scprodtest_diftypes\n");
	FreeVector(v1);
	FreeVector(v2);

}

void Test_VectorSum() {
	sumrealtest();
	sumrealtest_zero();
	sumrealtest_minus();
	sumrealtest_commut();
	sumrealtest_assoc();
	sumrealtest_num();
	sumcomplextest();
	sumcomplextest_zero();
	sumcomplextest_minus();
	sumcomplextest_commut();
	sumcomplextest_assoc();
	sumtest_diftypes();
	sumtest_difdims();
}

void Test_VectorScalarProduct() {
	scprodrealtest();
	scprodrealtest_zero();
	scprodrealtest_commut();
	scprodrealtest_num();
	scprodcomplextest();
	scprodcomplextest_zero();
	scprodcomplextest_commut();
	scprodtest_diftypes();
}