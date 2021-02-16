#pragma once
#ifndef _POLYNOMIALARITHMETIC_H_
#define _POLYNOMIALARITHMETIC_H_
#include "../Modular/ModularArithmetic.h"
#include <vector>

using CoefficientsType = std::vector<Int>;

CoefficientsType polynomial_add(const CoefficientsType& left, const CoefficientsType& right, const Int mod);
CoefficientsType polynomial_sub(const CoefficientsType& left, const CoefficientsType& right, const Int mod);
CoefficientsType polynomial_mul(const CoefficientsType& left, const CoefficientsType& right, const Int mod);
std::pair<CoefficientsType, CoefficientsType> polynomial_div(const CoefficientsType& left, const CoefficientsType& right, const Int mod);

Int polynomial_degree(CoefficientsType left);
#endif