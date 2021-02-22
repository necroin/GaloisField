#pragma once
#ifndef _GENERATOR_H_
#define _GENERATOR_H_
#include "../Field/GaloisField.h"


class Generator {
private:
	GaloisField _field;
	std::vector<GFElement> _A;
	std::vector<Number> _C;
	std::vector<GFElement> _Q;
public:
	Generator(GaloisField& field, Int N, const std::vector<GFElement> A, const std::vector<Number> C);

	void generate() {
		std::vector<GFElement> new_Q;
		new_Q.emplace_back(_A[0] * _Q[_Q.size() - 1] + _C[0]);
		for (size_t i = 1; i < _Q.size(); ++i) {
			new_Q.emplace_back(_A[i] * _Q[_Q.size() - 1] + _Q[i - 1] + _C[i]);
		}
		_Q = std::move(new_Q);
	}

	void print_state() {
		for (auto&& q : _Q) {
			std::cout << q.to_int() << " ";
		}
		std::cout << std::endl;
	}
};
#endif