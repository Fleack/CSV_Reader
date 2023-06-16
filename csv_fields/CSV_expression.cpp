#include "CSV_expression.h"

CSV_expression::CSV_expression(
	const std::string& column, long long row,
	const std::string& left_operand,
	const std::string& right_operand,
	std::shared_ptr<IOperation>& op) noexcept
	: CSV_field(column, row),
	left_operand(left_operand),
	right_operand(right_operand)
{
	this->op.swap(op);
}

CSV_expression::~CSV_expression() = default;

long long CSV_expression::get_value() const
{
	if (!value.has_value())
		value = (*op).get_result(left, right);
	return value.value();
}

void CSV_expression::set_left(const std::shared_ptr<CSV_field>& value)
{
	if (!correct_value(value, left_operand))
		throw std::runtime_error("The passed value is not consistent with data from the constructor");
	this->left = value;
}

void CSV_expression::set_right(const std::shared_ptr<CSV_field>& value)
{
	if (!correct_value(value, right_operand))
		throw std::runtime_error("The passed value is not consistent with data from the constructor");
	this->right = value;
}

const std::shared_ptr<CSV_field>& CSV_expression::get_left() const noexcept
{
	return left;
}

const std::shared_ptr<CSV_field>& CSV_expression::get_right() const noexcept
{
	return right;
}

const std::string& CSV_expression::get_left_operand() const noexcept
{
	return left_operand;
}

const std::string& CSV_expression::get_right_operand() const noexcept
{
	return right_operand;
}

bool CSV_expression::correct_value(const std::shared_ptr<CSV_field>& value, const std::string& exp_operand) const
{
	if (const std::shared_ptr<CSV_operation_number>& temp = std::dynamic_pointer_cast<CSV_operation_number> (value))
	{
		return (*temp).get_value() == std::stoll(exp_operand);
	}

	std::pair<std::string, long long> position = parse_operand(exp_operand);
	return position.first == (*value).get_column() && position.second == (*value).get_row();
}
