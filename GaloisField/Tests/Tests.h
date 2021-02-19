#pragma once
#ifndef _TESTS_H_
#define _TESTS_H_
#include "../Field/GaloisField.h"
#include <fstream>
#include <string>
namespace Tests {
	template <class _Left, class _Right, class _Operation, class _Result>
	class Test {
	private:
		bool _is_successful;
		_Left _left;
		_Right _right;
		_Operation _operation;
		std::string _operation_name;
		_Result _potential_result;
		_Result _real_result;
		Int _order_number;
		inline static Int _global_order_number = 1;
	public:
		Test(_Left left, _Right right, _Operation operation, _Result potential_result, std::string operation_name = "") :
			_left(left),
			_right(right),
			_operation(operation),
			_potential_result(potential_result),
			_operation_name(operation_name),
			_order_number(_global_order_number),
			_real_result(operation(left, right))
		{
			_is_successful = (_real_result == potential_result);
			++_global_order_number;
		}
	private:
		void brief_print(std::ostream& out) {
			out << "Test " << _order_number;
			if (_is_successful)
				out << " is successful" << std::endl;
			else
				out << " was failed" << std::endl;
			out << std::endl;
		}
		void full_print(std::ostream& out) {
			out << "Test " << _order_number << std::endl;
			out << "       Operation : " << _operation_name << std::endl;
			out << "    Left operand : " << _left << std::endl;
			out << "   Right operand : " << _right << std::endl;
			out << "     Real result : " << _real_result << std::endl;
			out << "Potential result : " << _potential_result << std::endl;
			if (_is_successful)
				out << "Test successful" << std::endl;
			else
				out << "Test failed" << std::endl;
			out << std::endl;
		}
	public:
		bool is_successful() const noexcept { return _is_successful; }

		void full_console_print() {
			full_print(std::cout);
		}
		void brief_console_print() {
			brief_print(std::cout);
		}
	};

	template <class _Left, class _Right, class _Operation, class _Result>
	Test(_Left, _Right, _Operation, _Result)->Test<_Left, _Right, _Operation, _Result>;

#define SIMPLE_GFELEMENTS_OPERATION(OPERATOR) [](const GFElement& left, const GFElement& right) { return left OPERATOR right; }

	void run_tests() {
		GaloisField field(2, 3, { 1,1,0,1 });
		decltype(auto) field_elements = field.all_field_elements();
		auto test1 = Test(field_elements[5], field_elements[7], SIMPLE_GFELEMENTS_OPERATION(*), field_elements[6], "a * b");
		test1.full_console_print();
		test1.brief_console_print();
	}
};
#endif