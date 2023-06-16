#pragma once
#include "CSV_field.h"

class CSV_operation_number : public CSV_field
{
public:
	CSV_operation_number(long long value) noexcept;

	long long get_value() const override;
};

