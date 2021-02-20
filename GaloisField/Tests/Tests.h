#pragma once
#ifndef _TESTS_H_
#define _TESTS_H_
#include "../Field/GaloisField.h"
#include <fstream>
#include <string>
#include <memory>
namespace Tests {

	class AbstractTest {
	protected:
		inline static Int _global_order_number = 1;
	public:
		virtual ~AbstractTest() = default;
		virtual void console_print() = 0;
	};

	template <class _Left, class _Right, class _Operation, class _Result>
	class Test : public AbstractTest {
	private:
		bool _is_successful;
		_Left _left;
		_Right _right;
		_Operation _operation;
		std::string _operation_name;
		_Result _potential_result;
		_Result _real_result;
		Int _order_number;
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
		void print(std::ostream& out) {
			if (_is_successful) {
				out << "Test " << _order_number << ": "
					<< _left << "  " << _operation_name << "  " << _right << " = " << _real_result 
					<< "  Successful" << std::endl;
			}
			else {
				out << std::endl;
				out << "Test " << _order_number << " failed"<< std::endl;
				out << "       Operation : " << _operation_name << std::endl;
				out << "    Left operand : " << _left << std::endl;
				out << "   Right operand : " << _right << std::endl;
				out << "     Real result : " << _real_result << std::endl;
				out << "Potential result : " << _potential_result << std::endl;
				out << std::endl;
			}
		}
	public:
		bool is_successful() const noexcept { return _is_successful; }

		virtual void console_print() override {
			print(std::cout);
		}
	};

	template <class _Left, class _Right, class _Operation, class _Result>
	Test(_Left, _Right, _Operation, _Result)->Test<_Left, _Right, _Operation, _Result>;

#define SIMPLE_GFELEMENTS_OPERATION(OPERATOR) [](const GFElement& left, const GFElement& right) { return left OPERATOR right; }
#define TEST(LEFT, RIGHT, OPERATION, RESULT, NAME) tests.emplace_back(std::unique_ptr<AbstractTest>(new Test(LEFT, RIGHT, OPERATION, RESULT, NAME)));
};
#endif