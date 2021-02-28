#pragma once
#ifndef _GENERATOR_H_
#define _GENERATOR_H_
#include "../Field/GaloisField.h"
#include <set>

class Generator {
private:
	GaloisField _field;
	std::vector<GFElement> _A;
	std::vector<Number> _C;
	std::vector<GFElement> _Q;
	std::vector<GFElement> _start_Q;
	Int _N;
private:
	void reset_Q();
public:
	Generator(GaloisField& field, Int N, std::vector<GFElement> A, std::vector<Number> C, std::vector<GFElement> star_Q = std::vector<GFElement>());
public:
	std::vector<GFElement> generate();
	void print_state(std::ostream& out = std::cout);
	void print_all_current_cycle_states(std::ostream& out = std::cout);
	std::vector<std::vector<std::vector<GFElement>>> generate_all_cycles();
	void print_all_cycles(std::ostream& out = std::cout);
};
#endif