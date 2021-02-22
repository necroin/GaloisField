#include <iostream>
#include "Field/GaloisField.h"
#include "Tests/TestsRun.h"
#include "Generator/Generator.h"





int main() {
	/*auto field = GaloisField(2, 2, { 1,1,1 });

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

	auto generator = Generator(field, N, A, C);*/

	///*generator.print_state();
	//for (size_t i = 0; i <= 10; ++i) {
	//	generator.generate();
	//	generator.print_state();
	//}*/
	
	decltype(auto) primitives = prim_poly::find_prim(7);
	for (auto&& primitive : primitives) {
		decltype(auto) primitive_it = primitive.begin();
		std::cout << "(";
		std::cout << *primitive_it++;
		for (; primitive_it != primitive.end(); ++primitive_it) {
			std::cout << "," << *primitive_it;
		}
		std::cout << ")" << std::endl;
	}

	system("pause");
	return 0;
}