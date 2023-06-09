#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include "CSV_field.h"
#include "CSV_value.h"
#include "CSV_expression.h"
#include "CSV_table.h"
#include "Plus.h"
#include "Minus.h"
#include "Multiplication.h"
#include "Division.h"
#include "IOperation.h"

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

