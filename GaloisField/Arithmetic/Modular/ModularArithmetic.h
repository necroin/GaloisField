#pragma once
#ifndef _MODULARARITHMETIC_H_
#define _MODULARARITHMETIC_H_
#include <exception>
#include <array>
using Int = long long int;

Int fast_power(Int base, Int power, Int mod);

Int modular_add(const Int left, const Int right, const Int mod);
Int modular_sub(const Int left, const Int right, const Int mod);
Int modular_mul(const Int left, const Int right, const Int mod);
Int modular_inv(const Int left, const Int mod);
Int modular_div(const Int left, const Int right, const Int mod);
#endif