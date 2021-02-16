#include "PolynomialArithmetic.h"

CoefficientsType polynomial_add(const CoefficientsType& left, const CoefficientsType& right, const Int mod)
{
	auto size = left.size();
	CoefficientsType ret_coefficients(size);
	for (size_t i = 0; i < size; ++i) {
		ret_coefficients[i] = modular_add(left[i], right[i], mod);
	}
	return std::move(ret_coefficients);
}

CoefficientsType polynomial_sub(const CoefficientsType& left, const CoefficientsType& right, const Int mod)
{
	auto size = left.size();
	CoefficientsType ret_coefficients(size);
	for (size_t i = 0; i < size; ++i) {
		ret_coefficients[i] = modular_sub(left[i], right[i], mod);
	}
	return std::move(ret_coefficients);
}

CoefficientsType polynomial_mul(const CoefficientsType& left, const CoefficientsType& right, const Int mod)
{
	CoefficientsType result(left.size() + right.size(), 0);
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

std::pair<CoefficientsType, CoefficientsType> polynomial_div(const CoefficientsType& left, const CoefficientsType& right, const Int mod)
{
	CoefficientsType quotient(left.size(),0);
	CoefficientsType remainder = left;
	CoefficientsType qRight(left.size(), 0);

	decltype(auto) remainder_degree = polynomial_degree(remainder);
	decltype(auto) right_degree = polynomial_degree(right);
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

Int polynomial_degree(CoefficientsType left)
{
	for (Int i = left.size() - 1; i >= 0; --i) {
		if (left[i]) return i;
	}
	return -1;
}
