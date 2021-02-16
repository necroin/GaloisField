#pragma once
#include "GFElement/GFElement.h"

class GaloisField {
private:
	Int _characteristic;
	Int _dimension;
	CoefficientsType _reduction_polynomial;
public:
	GaloisField(Int characteristic, Int dimension, CoefficientsType reduction_polynomial);
public:
	Int characteristic() const;
	Int dimension() const;
	const CoefficientsType& reduction_polynomial() const;
	GFElement create_polynomial(GFElement::CoefficientsType coefficients);
};