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
	const CSV_field* left, const CSV_field* right,
	std::shared_ptr<IOperation>& op) noexcept
	: CSV_field(column, row),
	left(left), right(right),
	left_column(left->get_column()), left_row(left->get_row()),
	right_column(right->get_column()), right_row(right->get_row())
{
	this->op.swap(op);
}

CSV_expression::~CSV_expression() = default;

long long CSV_expression::get_value() const
{
	// ÓÁÐÀÒÜ ÏÐÎÂÅÐÊÓ
	if (left == nullptr || right == nullptr)
	{
		return -100500;
	}
	return (*op).get_result(left, right);
}

void CSV_expression::set_left(const CSV_field* value)
{
	if (check_value(value))
		throw std::runtime_error(""); // îïèñàíèå
	this->left = value;
}

void CSV_expression::set_right(const CSV_field* value)
{
	if (check_value(value))
		throw std::runtime_error(""); // îïèñàíèå
	this->right = value;
}

bool CSV_expression::check_value(const CSV_field* value) const noexcept
{
	return !(value->get_column() != this->column || value->get_row() != this->row);
}
