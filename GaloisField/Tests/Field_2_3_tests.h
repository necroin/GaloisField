#pragma once
#ifndef _FIELD_2_3_TESTS_H_
#define _FIELD_2_3_TESTS_H_
#include "Tests.h"
namespace Tests {

	std::vector<std::unique_ptr<AbstractTest>> test_field_2_3() {
		GaloisField field(2, 3, { 1,1,0,1 });
		decltype(auto) field_elements = field.all_field_elements();
		std::vector<std::unique_ptr<AbstractTest>> tests;
		TEST(field_elements[0], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[0], "a + b");
		TEST(field_elements[0], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "a + b");
		TEST(field_elements[0], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[2], "a + b");
		TEST(field_elements[0], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[3], "a + b");
		TEST(field_elements[0], field_elements[4], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[4], "a + b");
		TEST(field_elements[0], field_elements[5], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[5], "a + b");
		TEST(field_elements[0], field_elements[6], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[6], "a + b");
		TEST(field_elements[0], field_elements[7], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[7], "a + b");

		//TEST(field_elements[1], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "a + b");
		//TEST(field_elements[1], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "a + b");
		//TEST(field_elements[1], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "a + b");
		//TEST(field_elements[1], field_elements[4], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "a + b");
		//TEST(field_elements[1], field_elements[5], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "a + b");
		//TEST(field_elements[1], field_elements[6], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "a + b");
		//TEST(field_elements[1], field_elements[7], SIMPLE_GFELEMENTS_OPERATION(+), field_elements[1], "a + b");

		TEST(field_elements[0], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[0], "a - b");
		TEST(field_elements[0], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[1], "a - b");
		TEST(field_elements[0], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[2], "a - b");
		TEST(field_elements[0], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[3], "a - b");
		TEST(field_elements[0], field_elements[4], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[4], "a - b");
		TEST(field_elements[0], field_elements[5], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[5], "a - b");
		TEST(field_elements[0], field_elements[6], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[6], "a - b");
		TEST(field_elements[0], field_elements[7], SIMPLE_GFELEMENTS_OPERATION(-), field_elements[7], "a - b");


		TEST(field_elements[0], field_elements[0], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "a * b");
		TEST(field_elements[0], field_elements[1], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "a * b");
		TEST(field_elements[0], field_elements[2], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "a * b");
		TEST(field_elements[0], field_elements[3], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "a * b");
		TEST(field_elements[0], field_elements[4], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "a * b");
		TEST(field_elements[0], field_elements[5], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "a * b");
		TEST(field_elements[0], field_elements[6], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "a * b");
		TEST(field_elements[0], field_elements[7], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[0], "a * b");


		//auto test1 = Test(field_elements[5], field_elements[7], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[6], "a * b")


		return tests;
	}
}
#endif