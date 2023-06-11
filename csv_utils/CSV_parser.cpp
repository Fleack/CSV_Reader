#include "CSV_parser.h"

CSV_parser::CSV_parser() noexcept {}

CSV_parser::~CSV_parser() {}

CSV_table CSV_parser::read(const std::string& filename)
{
	std::unique_ptr<std::ifstream> pfile = std::make_unique<std::ifstream>(filename);

	if (!(*pfile).is_open())
		throw std::runtime_error("Failed to open file");

	CSV_table table;
	size_t table_columns = -1;
	bool head = true;
	std::string line;

	while (std::getline(*pfile, line))
	{
		// Divide the string by ','
		std::vector< std::string > values;
		std::istringstream iss(line);
		std::string temp;
		while (std::getline(iss, temp, ','))
			values.push_back(temp);

		// If we read the title, then we remember the size for later comparison
		// Adding a separate column for each name
		if (head)
		{
			if (values.size() == 0 || values.size() == 1)
				throw std::runtime_error("Incorrect csv file");

			if (values[0] != "")
				throw std::runtime_error("Incorrect top left value of csv file. It has to be skipped");

			table.header = values;
			table_columns = values.size();
			for (size_t i = 1; i < table_columns; i++)
			{
				if (!is_string(table.header[i]))
					throw std::runtime_error("Name of column cannot consist of non-letter characters");

				if (table.table.find(table.header[i]) != table.table.end())
					throw std::runtime_error("Name of column already exists");

				std::unordered_map< long long, std::shared_ptr<CSV_field> > temp;
				table.table.insert(std::make_pair(table.header[i], std::move(temp)));
			}
			head = false;
		}
		// Otherwise, we check that the current line is equal in size to the header
		// Adding the line number to the vector
		// Insert the expression into the desired fields
		else
		{
			if (values.size() != table_columns)
				throw std::runtime_error("The size of the line is not consistent with the size of the header");

			long long cur_row = std::stoll(values[0]);

			if (table.table[table.header[1]].find(cur_row) != table.table[table.header[1]].end())
				throw std::runtime_error("Number of row already exists");

			table.rows.push_back(cur_row);

			for (size_t i = 1; i < table_columns; i++)
			{
				insert(values[i], table, table.header[i], cur_row);
			}
		}
	}

	if (table.header.empty() || table.rows.empty())
		throw std::runtime_error("Incorrect file structure (most likely the file is empty, or only the header is specified)");

	return table;
}

void CSV_parser::insert(const std::string& field, CSV_table& table, const std::string& column, long long row) const
{
	if (field.size() == 0)
		throw std::runtime_error("The field of csv file cannot be empty");

	if (is_number(field))
	{
		insert_value(field, table, column, row);
	}
	else
	{
		insert_expression(field, table, column, row);
	}
}

void CSV_parser::insert_value(const std::string& field, CSV_table& table, const std::string& column, long long row) const
{
	long long t = std::stoll(field);
	table.table[column][row] = std::make_shared<CSV_value>(column, row, t);
}

void CSV_parser::insert_expression(const std::string& field, CSV_table& table, const std::string& column, long long row) const
{
	const int MIN_EXPRESSION_LEN = 4; // =0+0 | smaller in size is not possible
	if (field.size() < MIN_EXPRESSION_LEN || field[0] != '=')
		throw std::runtime_error("Invalid expression syntax in csv file");

	size_t cur_pos = 1;

	std::string left_operand = get_operand(cur_pos, field);
	std::shared_ptr<IOperation> op = get_operation(cur_pos, field);
	std::string right_operand = get_operand(cur_pos, field);

	table.table[column][row] = std::make_shared<CSV_expression>(column, row, left_operand, right_operand, op);
}

std::string CSV_parser::get_operand(size_t& start_pos, const std::string& field) const
{
	const size_t start = start_pos;
	std::string operand = "";
	for (size_t i = start; i < field.size(); i++)
	{
		if ( is_letter(field[i]) || is_digit(field[i]) || (i == start && is_operator(field[i])) )
		{
			operand += field[i];
			start_pos++;
		}
		else
		{
			break;
		}
	}

	if (!is_operand_correct(operand))
		throw std::runtime_error("Invalid operand in one of the fields");

	return operand;
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
		throw std::runtime_error("Invalid operation syntax");

	start_pos++;
	return op;
}

bool CSV_parser::is_operand_correct(const std::string& operand) const noexcept
{
	if (is_number(operand))
		return true;

	bool letters = false;
	bool digits = false;

	// First there are only letters, then only numbers
	for (char c : operand)
	{
		if (is_letter(c))
		{
			if (digits)
				return false;
			letters = true;
		}
		else if (is_digit(c))
		{
			if (!letters)
				return false;
			digits = true;
		}
		else
		{
			return false;
		}
	}

	return letters && digits;
}