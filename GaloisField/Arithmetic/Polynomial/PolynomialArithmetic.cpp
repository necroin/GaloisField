#include "PolynomialArithmetic.h"

CoefficientsVector polynomial_add(const CoefficientsVector& left, const CoefficientsVector& right, const Int mod)
{
	auto size = left.size();
	CoefficientsVector result(size);
	for (size_t i = 0; i < size; ++i) {
		result[i] = modular_add(left[i], right[i], mod);
	}
	return result;
}

CoefficientsVector polynomial_sub(const CoefficientsVector& left, const CoefficientsVector& right, const Int mod)
{
	auto size = left.size();
	CoefficientsVector result(size);
	for (size_t i = 0; i < size; ++i) {
		result[i] = modular_sub(left[i], right[i], mod);
	}
	return result;
}

CoefficientsVector polynomial_mul(const CoefficientsVector& left, const CoefficientsVector& right, const Int mod)
{
	CoefficientsVector result(left.size() + right.size(), 0);
	for (size_t i = 0; i < result.size(); ++i) {
		for (size_t j = 0; j <= i; ++j) {
			if (i - j < right.size() && j < left.size()) {
				decltype(auto) temp = modular_mul(left[j], right[i - j], mod);
				result[i] = modular_add(result[i], temp, mod);
			}
		}
	}
	return result;
}

std::pair<CoefficientsVector, CoefficientsVector> polynomial_div(const CoefficientsVector& left, const CoefficientsVector& right, const Int mod)
{
	decltype(auto) right_degree = polynomial_degree(right);
	if (right_degree == -1) throw std::exception("divide by zero");

	CoefficientsVector quotient(left.size(),0);
	CoefficientsVector remainder = left;
	CoefficientsVector qRight(left.size(), 0);

	decltype(auto) remainder_degree = polynomial_degree(remainder);
	while (remainder_degree >= right_degree) {
		decltype(auto) q = modular_div(remainder[remainder_degree], right[right_degree], mod);

		decltype(auto) diff = remainder_degree - right_degree;

		quotient[diff] = q;

		for (Int i = right_degree; i >= 0; --i) {
			qRight[i + diff] = modular_mul(right[i], q, mod);
		}

		for (Int i = 0; i < diff; ++i) {
			qRight[i] = 0;
		}

		for (Int i = 0; i <= remainder_degree; ++i) {
			remainder[i] = modular_sub(remainder[i], qRight[i], mod);
		}

		remainder_degree = polynomial_degree(remainder);
	}

	return { quotient, remainder };
}

Int polynomial_degree(const CoefficientsVector& polynomial_coefficients)
{
	for (Int i = polynomial_coefficients.size() - 1; i >= 0; --i) {
		if (polynomial_coefficients[i]) return i;
	}
	return -1;
}

CoefficientsVector polinomial_inv(const CoefficientsVector& polynomial_coefficients, const Int mod)
{
	return CoefficientsVector();
}
