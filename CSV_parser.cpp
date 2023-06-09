#include "CSV.h"

CSV_parser::CSV_parser() noexcept {}

CSV_parser::~CSV_parser() {}

void CSV_parser::read(const std::string& filename)
{
	std::unique_ptr<std::ifstream> pfile = std::make_unique<std::ifstream>(filename);
	if (!(*pfile).is_open())
		throw std::runtime_error(""); // ��������

	size_t table_columns = -1;
	bool head = true;
	std::string line;
	while (std::getline(*pfile, line)) // ��������� ������ ����
	{
		// ���������� ���������� ������ �� ','
		std::vector< std::string > values;
		std::istringstream iss(line);
		std::string temp;
		while (std::getline(iss, temp, ','))
			values.push_back(temp);

		// ���� ������ ���������, �� ���������� ������ ��� ������������ ���������
		// ��������� ��� ������� �������� ���� �������
		if (head)
		{
			if (values.size() == 0 || values.size() == 1)
				throw std::runtime_error(""); // ��������

			header = values;
			table_columns = values.size();
			for (size_t i = 1; i < table_columns; i++)
			{
				if (!is_string(header[i]))
					throw std::runtime_error(""); // ��������
				// ���������, ��� �� ��� ������� � ����� �� ���������
				if (table.contains(header[i]))
					throw std::runtime_error(""); // ��������
				std::unordered_map< long long, std::shared_ptr<CSV_field> > temp;
				table.insert(std::make_pair(header[i], std::move(temp)));
			}
			head = false;
		}
		// ����� ���������, ��� ������� ������ �� ������� ����� ���������
		// ��������� ����� ������ � ������
		// ��������� � ������ ������ ���������
		else
		{
			if (values.size() != table_columns)
				throw std::runtime_error(""); // ��������

			long long cur_row = std::stoll(values[0]);

			// ���������, ��� �� ��� ������ � ����� �� �������
			if (table[header[1]].contains(cur_row))
				throw std::runtime_error(""); // ��������

			rows.push_back(cur_row);
			for (size_t i = 1; i < table_columns; i++)
			{
				insert(values[i], table, header[i], cur_row);
			}
		}
	}
}

const Table& CSV_parser::get_table() const noexcept
{
	return table;
}

const std::vector<std::string>& CSV_parser::get_header() const noexcept
{
	return header;
}

const std::vector<long long>& CSV_parser::get_rows() const noexcept
{
	return rows;
}

void CSV_parser::insert(const std::string& field, Table& table, const std::string& column, long long row) const
{
	if (field.size() == 0)
		throw std::runtime_error(""); // ��������

	if (is_number(field))
	{
		insert_value(field, table, column, row);
	}
	else
	{
		insert_expression(field, table, column, row);
	}
}

void CSV_parser::insert_value(const std::string& field, Table& table, const std::string& column, long long row) const noexcept
{
	long long t = std::stoll(field);
	table[column][row] = std::make_shared<CSV_value>(column, row, t);
}

void CSV_parser::insert_expression(const std::string& field, Table& table, const std::string& column, long long row) const
{
	const int MIN_EXPRESSION_LEN = 6; // =A1+A1, ������ ����������
	if (field.size() < MIN_EXPRESSION_LEN)
		throw std::runtime_error(""); // ��������

	if (field[0] != '=')
		throw std::runtime_error(""); // ��������

	size_t cur_pos = 1;
	std::string left_column = get_column(cur_pos, field);
	long long left_row = get_row(cur_pos, field);
	std::shared_ptr<IOperation> op = get_operation(cur_pos, field);
	std::string right_column = get_column(cur_pos, field);
	long long right_row = get_row(cur_pos, field);

	table[column][row] = std::make_shared<CSV_expression>(column, row, left_column, left_row, right_column, right_row, op);
}

long long CSV_parser::get_row(size_t& start_pos, const std::string& field) const
{
	long long row = 0;
	for (size_t i = start_pos; i < field.size(); i++)
	{
		if (is_digit(field[i]))
		{
			row = row * 10 + static_cast<long long>(field[i] - '0');
			start_pos++;
		}
		else
			break;
	}
	return row;
}

std::string CSV_parser::get_column(size_t& start_pos, const std::string& field) const
{
	std::string column = "";
	for (size_t i = start_pos; i < field.size(); i++)
	{
		if (is_letter(field[i]))
		{
			column += field[i];
			start_pos++;
		}
		else
			break;
	}
	return column;
}

std::shared_ptr<IOperation> CSV_parser::get_operation(size_t& start_pos, const std::string& field) const
{
	char operation = field[start_pos];
	std::shared_ptr<IOperation> op = nullptr;
	if (operation == '+')
	{
		op = std::make_shared<Plus>();
	}
	else if (operation == '-')
	{
		op = std::make_shared<Minus>();
	}
	else if (operation == '*')
	{
		op = std::make_shared<Multiplication>();
	}
	else if (operation == '/')
	{
		op = std::make_shared<Division>();
	}

	if (op == nullptr)
		throw std::runtime_error(""); // ��������

	start_pos++;
	return op;
}

inline bool CSV_parser::is_number(const std::string& field) const noexcept
{
	if (field.size() == 0)
		return false;

	for (char c : field)
	{
		if (!is_digit(c))
			return false;
	}

	return true;
}

inline bool CSV_parser::is_letter(char c) const noexcept
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

inline bool CSV_parser::is_digit(char c) const noexcept
{
	return (c >= '0' && c <= '9');
}

inline bool CSV_parser::is_string(const std::string& str) const noexcept
{
	if (str.size() == 0)
		return false;

	for (char c : str)
	{
		if (!is_letter(c))
			return false;
	}
	return true;
}