#include "Multiplication.h"

Multiplication::Multiplication() noexcept = default;

Multiplication::~Multiplication() = default;

long long Multiplication::get_result(const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right) const
{
	return (*left).get_value() * (*right).get_value();
}