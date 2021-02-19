#include "GFElement.h"
#include "../GaloisField.h"

GFElement::GFElement(const CoefficientsVector& coefficients, GaloisField& field) :
	_coefficients(coefficients),
	_field(field)
{}

GFElement::GFElement(CoefficientsVector&& coefficients, GaloisField& field) :
	_coefficients(coefficients),
	_field(field)
{}

GFElement::GFElement(const GFElement& left, const GFElement& right, decltype(polynomial_add) polynomial_operator) :
	_field(left._field),
	_coefficients(polynomial_operator(left._coefficients, right._coefficients, left._field.characteristic()))
{}

void GFElement::field_assert(const GFElement& other) const
{
	if (_field != other._field) throw std::exception("the fields are not compatible");
}

GFElement GFElement::operator+(const GFElement& other) const
{
	field_assert(other);
	return GFElement(*this, other, polynomial_add);
}

GFElement GFElement::operator-(const GFElement& other) const
{
	field_assert(other);
	return GFElement(*this, other, polynomial_sub);
}

GFElement GFElement::operator*(const GFElement& other) const
{
	field_assert(other);
	decltype(auto) product = polynomial_mul(_coefficients, other._coefficients, _field.characteristic());
	decltype(auto) reduction_polynomial = _field.reduction_polynomial();
	decltype(auto) reminder = polynomial_div(product, reduction_polynomial, _field.characteristic()).second;
	return GFElement(CoefficientsVector(reminder.begin(), reminder.begin() + _field.dimension()), _field);
}

GFElement GFElement::operator/(const GFElement& other) const
{
	field_assert(other);
	return (*this) * GFElement(polinomial_inv(other._coefficients, other._field.characteristic()), _field);
}

bool GFElement::operator==(const GFElement& other) const noexcept
{
	field_assert(other);
	for (size_t i = 0; i < _coefficients.size(); ++i) {
		if (_coefficients[i] != other._coefficients[i]) return false;
	}
	return true;
}

bool GFElement::operator!=(const GFElement& other) const noexcept
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const GFElement& element)
{
	decltype(auto) coefficients = element._coefficients;
	decltype(auto) coefficients_it = coefficients.begin();
	out << "[";
	out << *coefficients_it++;
	for (; coefficients_it != coefficients.end(); ++coefficients_it) {
		out << "," << *coefficients_it;
	}
	out << "]";
	return out;
}
