#pragma once
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "../Polynomial/PolynomialArithmetic.h"

class GFElement;

class Number {
private:
	friend class GFElement;
	CoefficientsVector _coefficients;
public: 
	Number(const CoefficientsVector& coefficients);
	Number(CoefficientsVector&& coefficients);
public:
	GFElement operator+(const GFElement& element);
};
#endif