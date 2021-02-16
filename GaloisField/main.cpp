#include <iostream>
#include "Field/GaloisField.h"

int main() {
	GaloisField field(2, 3, {1,1,0,1});
	auto a = field.create_polynomial({ 1,1,1 });
	auto b = field.create_polynomial({ 1,0,1 });
	auto c = a * b;

	for (auto&& coef : c._coefficients) {
		std::cout << coef << " ";
	}
	system("pause");
	return 0;
}