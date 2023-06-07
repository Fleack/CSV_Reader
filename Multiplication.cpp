#include "Multiplication.h"

Multiplication::Multiplication() noexcept = default;

Multiplication::~Multiplication() = default;

long long Multiplication::get_result(const CSV_field* left, const CSV_field* right) const noexcept
{
	return left->get_value() + right->get_value();
}