#pragma once
#include "vector.h"
#include "cmplx.h"

Vector VectorCreateReal();
Vector VectorCreateComplex();
Vector VectorCreate();
Vector VectorSumReal(Vector, Vector);
Vector VectorSumComplex(Vector, Vector);
Vector VectorSum(Vector, Vector);
double* VectorScalarProductReal(Vector, Vector);
complex* VectorScalarProductComplex(Vector, Vector);
void* VectorScalarProduct(Vector, Vector);
void FreeVector(Vector);



