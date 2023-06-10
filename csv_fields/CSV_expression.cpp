#include "CSV_expression.h"

CSV_expression::CSV_expression(
	const std::string& column, long long row,
	const std::string& left_column, long long left_row,
	const std::string& right_column, long long right_row,
	std::shared_ptr<IOperation>& op) noexcept
	: CSV_field(column, row),
	left_column(left_column), left_row(left_row),
	right_column(right_column), right_row(right_row)
{
	this->op.swap(op);
}

CSV_expression::CSV_expression(
	const std::string& column, long long row,
	const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right,
	std::shared_ptr<IOperation>& op) noexcept
	: CSV_field(column, row),
	left(left), right(right),
	left_column((*left).get_column()), left_row((*left).get_row()),
	right_column((*right).get_column()), right_row((*right).get_row())
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
	if (!correct_value(value, this->left_column, this->left_row))
		throw std::runtime_error("The passed value is not consistent with the column and row from the constructor");
	this->left = value;
}

void CSV_expression::set_right(const std::shared_ptr<CSV_field>& value)
{
	if (!correct_value(value, this->right_column, this->right_row))
		throw std::runtime_error("The passed value is not consistent with the column and row from the constructor");
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

const std::string& CSV_expression::get_left_column() const noexcept
{
	return left_column;
}

const std::string& CSV_expression::get_right_column() const noexcept
{
	return right_column;
}

long long CSV_expression::get_left_row() const noexcept
{
	return left_row;
}

long long CSV_expression::get_right_row() const noexcept
{
	return right_row;
}

bool CSV_expression::correct_value(const std::shared_ptr<CSV_field>& value, const std::string& exp_column, long long exp_row) const noexcept
{
	if ((*value).get_column() != exp_column)
		return false;
	if ((*value).get_row() != exp_row)
		return false;
	return true;
}
