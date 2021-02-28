#include <iostream>
#include "Field/GaloisField.h"
#include "Tests/TestsRun.h"
#include "Generator/Generator.h"

int main() {
	Int p = 2;
	Int n = 2;

	auto primitives = prim_poly::find_prim(n);

	auto field = GaloisField(p, n, primitives.front());

	Int N = 2;

	auto A = std::vector{
		field.create_polynomial({ 0,1 }),
		field.create_polynomial({ 1,0 })
	};

	auto C = std::vector{
		Number({ 0,0 }),
		Number({ 1,0 })
	};

	auto generator = Generator(field, N, A, C);

	std::ofstream file("Test.txt", std::ios_base::trunc);
	generator.print_all_cycles(file);
	file.close();
	system("pause");
	return 0;
}