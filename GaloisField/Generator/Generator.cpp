#include "Generator.h"

void Generator::reset_Q()
{
	_Q = _start_Q;
}

Generator::Generator(GaloisField& field, Int N, std::vector<GFElement> A, std::vector<Number> C, std::vector<GFElement> star_Q) :
	_field(field),
	_N(N),
	_A(A),
	_C(C)
{
	if (star_Q.size() == N) _start_Q = star_Q;
	else _start_Q = std::vector(N, GFElement(CoefficientsVector(field.dimension(), 0), field));
	reset_Q();
}

std::vector<GFElement> Generator::generate()
{
	std::vector<GFElement> new_Q;
	new_Q.emplace_back(_A[0] * _Q[_Q.size() - 1] + _C[0]);
	for (size_t i = 1; i < _Q.size(); ++i) {
		new_Q.emplace_back(_A[i] * _Q[_Q.size() - 1] + _Q[i - 1] + _C[i]);
	}
	_Q = std::move(new_Q);
	return _Q;
}

void Generator::print_state(std::ostream& out)
{
	for (auto&& q : _Q) {
		out << q.to_int() << " ";
	}
	out << std::endl;
}

void Generator::print_all_current_cycle_states(std::ostream& out)
{
	reset_Q();
	print_state(out);
	while (generate() != _start_Q) {
		print_state(out);
	}
}

std::vector<std::vector<std::vector<GFElement>>> Generator::generate_all_cycles()
{
	decltype(auto) all_field_polynomials = _field.all_field_elements(); 

	std::set<std::vector<GFElement>> all_polynomials_combinations_set;

	{
		auto combination = std::vector<GFElement>(_N, all_field_polynomials.front());
		auto max_combination = std::vector<GFElement>(_N, all_field_polynomials.back());

		while (combination != max_combination) {
			all_polynomials_combinations_set.insert(combination);
			for (auto&& q : combination) {
				if (q == all_field_polynomials.back()) q = all_field_polynomials.front();
				else {
					q = all_field_polynomials[q.to_int() + 1];
					break;
				}
			}
		}
		all_polynomials_combinations_set.insert(combination);
	}


	std::vector<std::vector<std::vector<GFElement>>> all_cycles;

	while (!all_polynomials_combinations_set.empty()) {
		auto start_Q = *all_polynomials_combinations_set.begin();
		_Q = start_Q;
		all_cycles.emplace_back(std::vector<std::vector<GFElement>>());
		decltype(auto) current_cycle = all_cycles.back();
		current_cycle.emplace_back(_Q);
		all_polynomials_combinations_set.erase(_Q);
		while (generate() != start_Q) {
			current_cycle.emplace_back(_Q);
			all_polynomials_combinations_set.erase(_Q);
		}
	}
	reset_Q();
	return all_cycles;
}

void Generator::print_all_cycles(std::ostream& out)
{
	decltype(auto) all_cycles = generate_all_cycles();
	Int cycle_counter = 0;
	for (auto&& cycle : all_cycles) {
		++cycle_counter;
		out << "Cycle -> " << cycle_counter << std::endl;
		out << "States count -> " << cycle.size() << std::endl;
		for (auto&& combination : cycle) {
			for (auto&& q : combination) {
				out << q.to_int() << " ";
			}
			out << std::endl;
		}
		out << std::endl;
	}
}
