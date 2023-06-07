#include "Minus.h"

Minus::Minus() noexcept = default;

Minus::~Minus() = default;

long long Minus::get_result(const CSV_field* left, const CSV_field* right) const noexcept
{
	return left->get_value() + right->get_value();
}