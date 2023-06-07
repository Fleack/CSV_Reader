#pragma once
#include "CSV_field.h"

class CSV_value : public CSV_field
{
public:
	CSV_value(const std::string& column, long long row, long long value) noexcept;

	~CSV_value();

	long long get_value() const override;

private:
	long long value;
};