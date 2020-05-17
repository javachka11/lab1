#pragma once
#include "vector.h"
#include "cmplx.h"

double VAbs(double);
void test_realVector(double*, int);
void test_complexVector(double*, int);
void sumrealtest();
void sumrealtest_zero();
void sumrealtest_minus();
void sumrealtest_commut();
void sumrealtest_assoc();
void sumrealtest_num();
void sumcomplextest();
void sumcomplextest_zero();
void sumcomplextest_minus();
void sumcomplextest_commut();
void sumcomplextest_assoc();
void sumtest_diftypes();
void sumtest_difdims();
void scprodrealtest();
void scprodrealtest_zero();
void scprodrealtest_commut();
void scprodrealtest_num();
void scprodcomplextest();
void scprodcomplextest_zero();
void scprodcomplextest_commut();
void scprodtest_diftypes();
void Test_VectorSum();
void Test_VectorScalarProduct();