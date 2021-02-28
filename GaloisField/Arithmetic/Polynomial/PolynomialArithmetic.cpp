#include "PolynomialArithmetic.h"
#include <iostream>

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

		Int from_binary(const CoefficientsVector& coefs) {
			Int result = 0;
			Int power2 = 1;
			for (auto coef : coefs) {
				result += coef * power2;
				power2 *= 2;
			}
			return result;
		}

		CoefficientsVector power2(Int degree, Int size)
		{
			CoefficientsVector res(size, 0);
			res[degree] = 1;
			return res;
		}

		CoefficientsVector binary_xor(const CoefficientsVector& left, const CoefficientsVector& right)
		{
			auto left_size = left.size();
			auto right_size = right.size();
			CoefficientsVector res;
			if (left_size < right_size) {
				res = right;
				for (size_t i = 0; i < left_size; ++i) {
					res[i] ^= left[i];
				}
			}
			else {
				res = left;
				for (size_t i = 0; i < right_size; ++i) {
					res[i] ^= right[i];
				}
			}
			return res;
		}

		std::pair<CoefficientsVector, CoefficientsVector> div_alg(const CoefficientsVector& left, const CoefficientsVector& right)
		{
			auto diff = polynomial_degree(left) - polynomial_degree(right);
			if (diff < 0) {
				return { CoefficientsVector{0} , left };
			}
			CoefficientsVector a(diff, 0);
			auto q = power2(diff, left.size());

			auto m = a;
			m.reserve(m.size() + right.size());
			m.insert(m.end(), right.begin(), right.end());

			
			auto r = binary_xor(m, left);

			auto [new_Q, new_R] = div_alg(r, right);
			return { binary_xor(new_Q, q),new_R };
		}
	}

	PolynomialsList poly_gen(Int degree)
	{
		PolynomialsList polynomials;
		for (int i = 1; i < pow(2, (degree - 1)) + 1; ++i) { // int64_t
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
		for (Int i = 2; i < pow(2, polynomial_deg) + 1; ++i) { // int64_t
			decltype(auto) j = detail::to_binary(i, polynomial.size());
			decltype(auto) R = detail::div_alg(polynomial, j).second;
			if (polynomial_degree(R) == -1) return false;
		}
		return true;
	}

	bool check_div(const CoefficientsVector& left, const CoefficientsVector& right)
	{
		if (polynomial_degree(left) == polynomial_degree(right)) return false;
		decltype(auto) R = detail::div_alg(left, right).second;
		if (detail::from_binary(R) == 0) return true;
		return false;
	}

	Int poly_order(const CoefficientsVector& polynomial)
	{
		auto max_T = pow(2, polynomial.size() - 1); // int64_t
		for (Int T = polynomial.size() - 1; T < max_T; ++T) {
			decltype(auto) poly = detail::power2(T, T + 1);
			poly[T] = 1;
			poly[0] = 1;
			if (check_div(poly, polynomial)) return T;
		}
		return -1;
	}

	PolynomialsList find_prim(Int degree)
	{
		decltype(auto) canditates = poly_gen(degree);
		PolynomialsList primitives;
		for (auto&& polynomial : canditates) {
			if (check_irr(polynomial)){
				auto _poly_order = poly_order(polynomial);
				auto power = static_cast<Int>(pow(2, degree) - 1); // int64_t
				if (_poly_order == power) {
					primitives.push_back(polynomial);
				}
			}
		}
		return primitives;
	}

	
}

void prim_poly::detail::debug::plynomial_print(const CoefficientsVector& polynomial_coefficients)
{
	decltype(auto) coefficients_it = polynomial_coefficients.begin();
	std::cout << "(";
	std::cout << *coefficients_it++;
	for (; coefficients_it != polynomial_coefficients.end(); ++coefficients_it) {
		std::cout << "," << *coefficients_it;
	}
	std::cout << ")" << std::endl;
}
