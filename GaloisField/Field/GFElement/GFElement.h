#pragma once
#ifndef _GFELEMENT_H_
#define _GFELEMENT_H_
#include "../../Arithmetic/Modular/ModularArithmetic.h"
#include "../../Arithmetic/Polynomial/PolynomialArithmetic.h"
#include <iostream>
class GaloisField;

class GFElement {
private:
	CoefficientsVector _coefficients;
	GaloisField& _field;
private:
	void field_assert(const GFElement& other) const;
public:
	GFElement operator+(const GFElement& other) const;
	GFElement operator-(const GFElement& other) const;
	GFElement operator*(const GFElement& other) const;
	GFElement operator/(const GFElement& other) const;

	bool operator == (const GFElement& other) const noexcept;
	bool operator != (const GFElement& other) const noexcept;
public:
	GFElement() = delete;
	GFElement(const GFElement&) = default;
	GFElement(GFElement&&) = default;

	GFElement(const CoefficientsVector& coefficients, GaloisField& field);
	GFElement(CoefficientsVector&& coefficients, GaloisField& field);
	GFElement(const GFElement& left, const GFElement& right, decltype(polynomial_add) polynomial_operator);

	GFElement& operator=(const GFElement&) = default;
	GFElement& operator=(GFElement&&) = default;
public:
	friend std::ostream& operator << (std::ostream& out, const GFElement& element);
};
#endif