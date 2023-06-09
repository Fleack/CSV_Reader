#include "CSV_field.h"

CSV_field::CSV_field(const std::string& column, long long row)
	: column(column), row(row)
{
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