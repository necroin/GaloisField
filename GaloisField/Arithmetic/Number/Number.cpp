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

bool BinaryNumber::operator<(const BinaryNumber& other)
{
	if (polynomial_degree(other._coefficients) > polynomial_degree(_coefficients)) {
		return true;
	}
	return false;
}

BinaryNumber& BinaryNumber::operator++()
{
	if (_coefficients.empty()) {
		_coefficients.push_back(1);
	}
	else {
		_coefficients[0] += 1;
		Int i = 0;
		while (_coefficients[i] == 2) {
			_coefficients[i] = 0;
			if (i == _coefficients.size() - 1) {
				_coefficients.push_back(1);
			}
			else {
				_coefficients[i + 1] += 1;
			}
			++i;
		}
	}
	return *this;
}
