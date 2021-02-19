#pragma once
#ifndef _TESTSRUN_H_
#define _TESTSRUN_H_
#include "Field_2_3_tests.h"
namespace Tests {

	void run_tests() {
		decltype(auto) tests = test_field_2_3();

		for (auto&& test : tests) {
			test->brief_console_print();
		}
	}
}
#endif