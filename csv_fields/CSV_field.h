#pragma once
#include <string>
#include <optional>

class CSV_field
{
public:
	CSV_field(const std::string& column, long long row) noexcept;

	CSV_field(const std::string& column, long long row, long long value) noexcept;

	virtual ~CSV_field();

	virtual long long get_value() const = 0;

	const std::string& get_column() const noexcept;

	long long get_row() const noexcept;

protected:
	const std::string column;

	const long long row;

	mutable std::optional<long long> value;
};