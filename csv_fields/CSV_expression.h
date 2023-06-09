#pragma once
#include <string>
#include <memory>
#include <stdexcept>

#include "CSV_field.h"
#include "CSV_operation_number.h"

#include "../csv_operations/IOperation.h"

#include "../csv_utils/CSV_utilfunc.h"

class CSV_expression : public CSV_field
{
public:
	CSV_expression(
		const std::string& column, long long row,
		const std::string& left_operand,
		const std::string& right_operand,
		std::shared_ptr<IOperation>& op) noexcept;

	~CSV_expression();

	long long get_value() const override;

	void set_left(const std::shared_ptr<CSV_field>& value);

	void set_right(const std::shared_ptr<CSV_field>& value);

	const std::shared_ptr<CSV_field>& get_left() const noexcept;

	const std::shared_ptr<CSV_field>& get_right() const noexcept;

	const std::string& get_left_operand() const noexcept;

	const std::string& get_right_operand() const noexcept;

private:
	const std::string left_operand;
	const std::string right_operand;

	std::shared_ptr<CSV_field> left;
	std::shared_ptr<CSV_field> right;

	std::shared_ptr<IOperation> op = nullptr;

	bool correct_value(const std::shared_ptr<CSV_field>& value, const std::string& exp_operand) const;
};