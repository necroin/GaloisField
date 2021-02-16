#include "GFElement.h"
#include "../GaloisField.h"

GFElement::GFElement(CoefficientsType coefficients, GaloisField& field) :
	_coefficients(coefficients),
	_field(field)
{}

GFElement::GFElement(const GFElement& left, const GFElement& right, decltype(polynomial_add) polynomial_operator) :
	_field(left._field),
	_coefficients(std::move(polynomial_operator(left._coefficients, right._coefficients, left._field.characteristic())))
{}

GFElement GFElement::operator+(const GFElement& other) const
{
	return GFElement(*this, other, polynomial_add);
}

GFElement GFElement::operator-(const GFElement& other) const
{
	return GFElement(*this, other, polynomial_sub);
}

GFElement GFElement::operator*(const GFElement& other) const
{
	decltype(auto) product = polynomial_mul(_coefficients, other._coefficients, _field.characteristic());
	decltype(auto) reduction_polynomial = _field.reduction_polynomial();
	decltype(auto) reminder = polynomial_div(product, reduction_polynomial, _field.characteristic()).second;
	return GFElement(CoefficientsType(reminder.begin(), reminder.begin() + _field.dimension()), _field);
}

GFElement GFElement::operator/(const GFElement& other) const
{
	return GFElement(*this, other, polynomial_add);
}

