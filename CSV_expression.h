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
		const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right,
		std::shared_ptr<IOperation>& op) noexcept;

	~CSV_expression();

	long long get_value() const override;

	void set_left(const std::shared_ptr<CSV_field>& value);

	void set_right(const std::shared_ptr<CSV_field>& value);

	const std::shared_ptr<CSV_field>& get_left() const noexcept;

	const std::shared_ptr<CSV_field>& get_right() const noexcept;

	const std::string& get_left_column() const noexcept;

	const std::string& get_right_column() const noexcept;

	long long get_left_row() const noexcept;

	long long get_right_row() const noexcept;

private:
	const std::string left_column;
	const std::string right_column;

	const long long left_row;
	const long long right_row;

	std::shared_ptr<CSV_field> left;
	std::shared_ptr<CSV_field> right;

	std::shared_ptr<IOperation> op = nullptr;

	bool correct_value(const std::shared_ptr<CSV_field>& value, const std::string& exp_column, long long exp_row) const noexcept;
};