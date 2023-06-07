#pragma once
#include <string>
#include <memory>
#include <stdexcept>

#include "CSV_field.h"
#include "IOperation.h"

class CSV_expression : public CSV_field
{
public:
	CSV_expression(
		const std::string& column, long long row,
		const std::string& left_column, long long left_row,
		const std::string& right_column, long long right_row,
		std::shared_ptr<IOperation>& op) noexcept;

	CSV_expression(
		const std::string& column, long long row,
		const CSV_field* left, const CSV_field* right,
		std::shared_ptr<IOperation>& op) noexcept;

	~CSV_expression();

	long long get_value() const override;

	void set_left(const CSV_field* value);

	void set_right(const CSV_field* value);

private:
	const std::string left_column;
	const std::string right_column;

	const long long left_row;
	const long long right_row;

	const CSV_field* left = nullptr;
	const CSV_field* right = nullptr;

	std::shared_ptr<IOperation> op = nullptr;

	bool check_value(const CSV_field* value) const noexcept;
};