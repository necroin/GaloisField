#pragma once
#ifndef _FIELD_2_2_TESTS_H_
#define _FIELD_2_2_TESTS_H_
#include "Tests.h"
namespace Tests {

	std::vector<std::unique_ptr<AbstractTest>> test_field_2_2() {
		GaloisField field(2, 2, { 1,1,1 });
		decltype(auto) field_elements = field.all_field_elements();
		std::vector<std::unique_ptr<AbstractTest>> tests;

		TEST(field_elements[0], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[0], "+");
		TEST(field_elements[0], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "+");
		TEST(field_elements[0], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[2], "+");
		TEST(field_elements[0], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[3], "+");

		TEST(field_elements[1], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "+");
		TEST(field_elements[1], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[0], "+");
		TEST(field_elements[1], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[3], "+");
		TEST(field_elements[1], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[2], "+");

		TEST(field_elements[2], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[2], "+");
		TEST(field_elements[2], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[3], "+");
		TEST(field_elements[2], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[0], "+");
		TEST(field_elements[2], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "+");

		TEST(field_elements[3], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[3], "+");
		TEST(field_elements[3], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[2], "+");
		TEST(field_elements[3], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "+");
		TEST(field_elements[3], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[0], "+");



		TEST(field_elements[0], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[0], "-");
		TEST(field_elements[0], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[1], "-");
		TEST(field_elements[0], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[2], "-");
		TEST(field_elements[0], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[3], "-");

		TEST(field_elements[1], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[1], "-");
		TEST(field_elements[1], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[0], "-");
		TEST(field_elements[1], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[3], "-");
		TEST(field_elements[1], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[2], "-");

		TEST(field_elements[2], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[2], "-");
		TEST(field_elements[2], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[3], "-");
		TEST(field_elements[2], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[0], "-");
		TEST(field_elements[2], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[1], "-");

		TEST(field_elements[3], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[3], "-");
		TEST(field_elements[3], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[2], "-");
		TEST(field_elements[3], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[1], "-");
		TEST(field_elements[3], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[0], "-");



		TEST(field_elements[0], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "*");
		TEST(field_elements[0], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "*");
		TEST(field_elements[0], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "*");
		TEST(field_elements[0], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "*");

		TEST(field_elements[1], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "*");
		TEST(field_elements[1], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[1], "*");
		TEST(field_elements[1], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[2], "*");
		TEST(field_elements[1], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[3], "*");

		TEST(field_elements[2], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "*");
		TEST(field_elements[2], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[2], "*");
		TEST(field_elements[2], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[3], "*");
		TEST(field_elements[2], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[1], "*");

		TEST(field_elements[3], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "*");
		TEST(field_elements[3], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[3], "*");
		TEST(field_elements[3], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[1], "*");
		TEST(field_elements[3], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[2], "*");

		return tests;
	}
}
#endif