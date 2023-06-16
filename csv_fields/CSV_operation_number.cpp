#include "CSV_operation_number.h"

CSV_operation_number::CSV_operation_number(long long value) noexcept
	: CSV_field("-1", -1, value)
{
}

long long CSV_operation_number::get_value() const
{
	return value.value();
}