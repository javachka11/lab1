#include "Test.h"
#include "shell.h"

int main() {

	Test_VectorSum();
	Test_VectorScalarProduct();
	printf("\n\n");

	Vector v1 = VectorCreate();
	Vector v2 = VectorCreate();
	Vector v_sum = VectorSum(v1, v2);
	complex z = VectorScalarProduct(v1, v2);
	VectorOutput(v_sum);
	complexOutput(z);
	
	FreeVector(v1);
	FreeVector(v2);
	FreeVector(v_sum);
}
