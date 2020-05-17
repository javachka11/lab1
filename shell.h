#pragma once
#include "vector.h"
#include "cmplx.h"

void VectorOutput(Vector);
Vector VectorCreateReal();
Vector VectorCreateComplex();
Vector VectorCreate();
Vector VectorSumReal(Vector, Vector);
Vector VectorSumComplex(Vector, Vector);
Vector VectorSumRealComplex(Vector, Vector);
Vector VectorSum(Vector, Vector);
complex VectorScalarProductReal(Vector, Vector);
complex VectorScalarProductComplex(Vector, Vector);
complex VectorScalarProductRealComplex(Vector, Vector);
complex VectorScalarProduct(Vector, Vector);
void FreeVector(Vector);



