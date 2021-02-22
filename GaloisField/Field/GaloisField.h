#pragma once
#ifndef _GALOISFIELD_H_
#define _GALOISFIELD_H_
#include "GFElement/GFElement.h"

class GaloisField {
private:
	Int _characteristic;
	Int _dimension;
	CoefficientsVector _reduction_polynomial;
public:
	GaloisField(Int characteristic, Int dimension, CoefficientsVector reduction_polynomial);
	GaloisField(Int characteristic, Int dimension);
public:
	Int characteristic() const noexcept;
	Int dimension() const noexcept;
	const CoefficientsVector& reduction_polynomial() const noexcept;
	GFElement create_polynomial(const CoefficientsVector& coefficients);
	GFElement create_polynomial(CoefficientsVector&& coefficients);
	std::vector<GFElement> all_field_elements();
public:
	bool operator == (const GaloisField& other) const noexcept;
	bool operator != (const GaloisField& other) const noexcept;
};
#endif