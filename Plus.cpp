#include "Plus.h"

Plus::Plus() noexcept = default;

Plus::~Plus() = default;

long long Plus::get_result(const CSV_field* left, const CSV_field* right) const noexcept
{
	return left->get_value() + right->get_value();
}