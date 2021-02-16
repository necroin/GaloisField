#pragma once
#ifndef _GFELEMENT_H_
#define _GFELEMENT_H_
#include <vector>
#include "../../Arithmetic/Modular/ModularArithmetic.h"
#include "../../Arithmetic/Polynomial/PolynomialArithmetic.h"

class GaloisField;

class GFElement {
public:
	using CoefficientsType = std::vector<Int>;
public:
	CoefficientsType _coefficients;
	GaloisField& _field;
public:
	GFElement operator+(const GFElement& other) const;
	GFElement operator-(const GFElement& other) const;
	GFElement operator*(const GFElement& other) const;
	GFElement operator/(const GFElement& other) const;
public:
	GFElement(CoefficientsType coefficients, GaloisField& field);
	GFElement(const GFElement& left, const GFElement& right, decltype(polynomial_add) polynomial_operator);
};
#endif