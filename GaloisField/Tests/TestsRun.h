#pragma once
#ifndef _TESTSRUN_H_
#define _TESTSRUN_H_
#include "Field_2_2_tests.h"
#include "Field_2_3_tests.h"
namespace Tests {

	template<class _TestFunction>
	void run_tests(_TestFunction test_function) {
		decltype(auto) tests = test_function();

		for (auto&& test : tests) {
			test->console_print();
		}
	}
}
#endif