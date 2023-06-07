#include "CSV_value.h"

CSV_value::CSV_value(const std::string& column, long long row, long long value) noexcept
	: CSV_field(column, row), value(value)
{
}

CSV_value::~CSV_value() = default;

long long CSV_value::get_value() const
{
	return value;
}