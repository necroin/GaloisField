#pragma once
#ifndef _GFELEMENT_H_
#define _GFELEMENT_H_
#include "../../Arithmetic/Modular/ModularArithmetic.h"
#include "../../Arithmetic/Polynomial/PolynomialArithmetic.h"
#include <iostream>
#include "../../Arithmetic/Number/Number.h"

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

	GFElement operator^(const Int degree) const;

	bool operator == (const GFElement& other) const noexcept;
	bool operator != (const GFElement& other) const noexcept;
	bool operator <  (const GFElement& other) const noexcept;
	bool operator >  (const GFElement& other) const noexcept;
	bool operator <= (const GFElement& other) const noexcept;
	bool operator >= (const GFElement& other) const noexcept;

public:
	GFElement operator+(const Number& other) const;
public:
	GFElement() = delete;
	GFElement(const GFElement& other);
	GFElement(GFElement&& other) noexcept;

	GFElement(const CoefficientsVector& coefficients, GaloisField& field);
	GFElement(CoefficientsVector&& coefficients, GaloisField& field);
	GFElement(const GFElement& left, const GFElement& right, decltype(polynomial_add) polynomial_operator);

	GFElement& operator=(const GFElement& other);
	GFElement& operator=(GFElement&& other) noexcept;
public:
	friend std::ostream& operator << (std::ostream& out, const GFElement& element);
public:
	Int to_int() const;
};
#endif