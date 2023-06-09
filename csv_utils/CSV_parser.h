#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include "CSV_table.h"

#include "../csv_fields/CSV_field.h"
#include "../csv_fields/CSV_value.h"
#include "../csv_fields/CSV_expression.h"

#include "../csv_operations/Plus.h"
#include "../csv_operations/Minus.h"
#include "../csv_operations/Multiplication.h"
#include "../csv_operations/Division.h"
#include "../csv_operations/IOperation.h"

class CSV_parser
{
public:
	CSV_parser() noexcept;

	~CSV_parser();

	CSV_table read(const std::string& filename);

private:

	void insert(const std::string& field, CSV_table& table, const std::string& column, long long row) const;

	void insert_value(const std::string& field, CSV_table& table, const std::string& column, long long row) const;

	void insert_expression(const std::string& field, CSV_table& table, const std::string& column, long long row) const;

	long long get_row(size_t& start_pos, const std::string& field) const;

	std::string get_column(size_t& start_pos, const std::string& field) const;

	std::shared_ptr<IOperation> get_operation(size_t& start_pos, const std::string& field) const;

	bool is_number(const std::string& field) const noexcept;

	inline bool is_letter(char c) const noexcept;

	inline bool is_digit(char c) const noexcept;

	inline bool is_string(const std::string& str) const noexcept;
};

