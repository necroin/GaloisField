#include "GaloisField.h"

GaloisField::GaloisField(Int characteristic, Int dimension, CoefficientsVector reduction_polynomial) :
	_characteristic(characteristic),
	_dimension(dimension),
	_reduction_polynomial(reduction_polynomial)
{}

Int GaloisField::characteristic() const noexcept
{
	return _characteristic;
}

Int GaloisField::dimension() const noexcept
{
	return _dimension;
}

const CoefficientsVector& GaloisField::reduction_polynomial() const noexcept
{
	return _reduction_polynomial;
}

GFElement GaloisField::create_polynomial(const CoefficientsVector& coefficients)
{
	return GFElement(coefficients, *this);
}

GFElement GaloisField::create_polynomial(CoefficientsVector&& coefficients)
{
	return GFElement(coefficients, *this);
}

std::vector<GFElement> GaloisField::all_field_elements()
{
	std::vector<GFElement> elements;
	CoefficientsVector coefficients(_dimension, 0);
	CoefficientsVector max_coefficients(_dimension, _characteristic - 1);
	while (coefficients != max_coefficients)
	{
		elements.emplace_back(coefficients, *this);
		coefficients[0] += 1;
		for (size_t i = 0; i < coefficients.size() - 1; ++i) {
			Int over_mod = coefficients[i] / _characteristic;
			coefficients[i] = coefficients[i] % _characteristic;
			coefficients[i + 1] += over_mod;
		}
	}
	elements.emplace_back(coefficients, *this);
	return elements;
}

bool GaloisField::operator==(const GaloisField& other) const noexcept
{
	return (_characteristic == other._characteristic) && (_dimension == other._dimension);
}

bool GaloisField::operator!=(const GaloisField& other) const noexcept
{
	return !(*this == other);
}
