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

namespace prim_poly {
	namespace detail {
		CoefficientsVector to_binary(Int number, Int size, const CoefficientsVector& begin_value)
		{
			CoefficientsVector result = begin_value;
			Int extractor = 1;
			for (Int i = 0; i < size; ++i) {
				result.push_back((number & extractor) > 0);
				extractor <<= 1;
			}
			return result;
		}
	}

	PolynomialsList poly_gen(Int degree)
	{
		PolynomialsList polynomials;
		for (int i = 1; i < pow(2, (degree - 1)) + 1; ++i) {
			auto poly = detail::to_binary(i, degree - 1, { 1 });
			Int checksum = 0;
			for (size_t i = 1; i < poly.size(); ++i) {
				checksum += poly[i];
			}
			if (checksum % 2 == 1) {
				poly.push_back(1);
				polynomials.push_back(poly);
			}
		}
		return polynomials;
	}

	bool check_irr(const CoefficientsVector& polynomial)
	{
		decltype(auto) polynomial_deg = polynomial_degree(polynomial);
		for (Int i = 2; i < pow(2, polynomial_deg) + 1; ++i) {
			decltype(auto) j = detail::to_binary(i, polynomial.size());
			decltype(auto) R = polynomial_div(polynomial, j, 2).second;
			if (polynomial_degree(R) == -1) return false;
		}
		return true;
	}

	bool check_div(const CoefficientsVector& left, const CoefficientsVector& right)
	{
		if (polynomial_degree(left) == polynomial_degree(right)) return false;
		decltype(auto) R = polynomial_div(left, right, 2).second;
		if (polynomial_degree(R) == -1) return true;
		return false;
	}

	Int poly_order(const CoefficientsVector& polynomial)
	{
		for (Int T = polynomial.size() - 1; T < pow(2, polynomial.size() - 1);++T) {
			decltype(auto) poly = detail::to_binary(pow(2, T) + 1, T + 1);
			if (check_div(poly, polynomial)) return T;
		}
		return -1;
	}

	PolynomialsList find_prim(Int degree)
	{
		decltype(auto) canditates = poly_gen(degree);
		PolynomialsList primitives;
		for (auto&& polynomial : canditates) {
			if (check_irr(polynomial) && (poly_order(polynomial) == (pow(2, degree) - 1))) {
				primitives.push_back(polynomial);
			}
		}
		return primitives;
	}

	
}