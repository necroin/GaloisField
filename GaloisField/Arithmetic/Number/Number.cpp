#include "Number.h"
#include "../../Field/GFElement/GFElement.h"

Number::Number(const CoefficientsVector& coefficients) : 
	_coefficients(coefficients)
{}

Number::Number(CoefficientsVector&& coefficients) : 
	_coefficients(coefficients)
{}

GFElement Number::operator+(const GFElement & element)
{
	return element + *this;
}
