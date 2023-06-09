#include "Plus.h"

Plus::Plus() noexcept = default;

Plus::~Plus() = default;

long long Plus::get_result(const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right) const
{
	return (*left).get_value() + (*right).get_value();
}