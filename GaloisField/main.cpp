#include <iostream>
#include "Field/GaloisField.h"
#include "Tests/TestsRun.h"
#include "Generator/Generator.h"

int main() {
	Tests::run_tests(Tests::test_field_2_2);

	auto field = GaloisField(2, 2, { 1,1,1 });

	Int N = 3;

	auto A = std::vector{
		field.create_polynomial({ 0,1 }),
		field.create_polynomial({ 1,1 }),
		field.create_polynomial({ 0,0 })
	};

	auto C = std::vector{
		Number({ 0,0 }),
		Number({ 0,0 }),
		Number({ 1,0 })
	};

	auto generator = Generator(field, N, A, C);

	generator.print_state();
	for (size_t i = 0; i <= 10; ++i) {
		generator.generate();
		generator.print_state();
	}
	system("pause");
	return 0;
}