#include "Minus.h"

Minus::Minus() noexcept = default;

Minus::~Minus() = default;

long long Minus::get_result(const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right) const noexcept
{
	return (*left).get_value() - (*right).get_value();
}