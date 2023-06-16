#include "Division.h"

Division::Division() noexcept = default;

Division::~Division() = default;

long long Division::get_result(const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right) const
{
	if ((*right).get_value() == 0)
		throw std::runtime_error("Division by zero in csv file");

	return (*left).get_value() / (*right).get_value();
}