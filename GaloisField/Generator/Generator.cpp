#include "Generator.h"




Generator::Generator(GaloisField& field, Int N, const std::vector<GFElement> A, const std::vector<Number> C) :
	_field(field),
	_A(A),
	_C(C),
	_Q(N, GFElement(CoefficientsVector(field.dimension(), 0), field))
{}
