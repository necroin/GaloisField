#pragma once
#ifndef _POLYNOMIALARITHMETIC_H_
#define _POLYNOMIALARITHMETIC_H_
#include "../Modular/ModularArithmetic.h"
#include <vector>

using CoefficientsVector = std::vector<Int>;

CoefficientsVector polynomial_add(const CoefficientsVector& left, const CoefficientsVector& right, const Int mod);
CoefficientsVector polynomial_sub(const CoefficientsVector& left, const CoefficientsVector& right, const Int mod);
CoefficientsVector polynomial_mul(const CoefficientsVector& left, const CoefficientsVector& right, const Int mod);
std::pair<CoefficientsVector, CoefficientsVector> polynomial_div(const CoefficientsVector& left, const CoefficientsVector& right, const Int mod);

Int polynomial_degree(const CoefficientsVector& polynomial_coefficients);

CoefficientsVector polinomial_inv(const CoefficientsVector& polynomial_coefficients, const Int mod);
#endif