#include "ModularArithmetic.h"

Int fast_power(Int base, Int power, Int mod) {
    Int result = 1;
    while (power > 0) {

        if ((power & 1) == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        power = power >> 1;
    }
    return result;
}


Int modular_add(Int left, Int right, Int mod)
{
	return (left + right) % mod;
}

Int modular_sub(Int left, Int right, Int mod)
{
	return (left + (mod - right)) % mod;
}

Int modular_mul(Int left, Int right, Int mod)
{
	return (left * right) % mod;
}

Int modular_inv(const Int left, const Int mod)
{
	return fast_power(left, mod - 2, mod);
}

Int modular_div(Int left, Int right, Int mod)
{
	if (right == 0) {
		throw std::exception("divide by zero");
	}
	return (left * modular_inv(right, mod)) % mod;
}
