#include "GaloisField.h"

GaloisField::GaloisField(Int characteristic, Int dimension, CoefficientsType reduction_polynomial) :
	_characteristic(characteristic),
	_dimension(dimension),
	_reduction_polynomial(reduction_polynomial)
{}

Int GaloisField::characteristic() const
{
	return _characteristic;
}

Int GaloisField::dimension() const
{
	return _dimension;
}

const CoefficientsType& GaloisField::reduction_polynomial() const
{
	return _reduction_polynomial;
}

GFElement GaloisField::create_polynomial(GFElement::CoefficientsType coefficients)
{
	return GFElement(coefficients, *this);
}
