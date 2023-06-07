#pragma once
#include <string>

class CSV_field
{
public:
	CSV_field(const std::string& column, long long row);

	virtual ~CSV_field();

	virtual long long get_value() const = 0;

	const std::string& get_column() const noexcept;

	long long get_row() const noexcept;

protected:
	const std::string column;

	const long long row;
};