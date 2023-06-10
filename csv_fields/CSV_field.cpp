#include "CSV_field.h"

CSV_field::CSV_field(const std::string& column, long long row) noexcept
	: column(column), row(row), value(std::nullopt)
{
}

CSV_field::CSV_field(const std::string& column, long long row, long long value) noexcept
	: CSV_field(column, row)
{
	this->value = value;
}

CSV_field::~CSV_field() = default;

const std::string& CSV_field::get_column() const noexcept
{
	return this->column;
}

long long CSV_field::get_row() const noexcept
{
	return this->row;
}