#pragma once
#include <unordered_set>

#include "CSV_table.h"

#include "../csv_fields/CSV_expression.h"

class CSV_cyclic_dependency
{
public:

	CSV_cyclic_dependency() noexcept;

	~CSV_cyclic_dependency();

	bool has_cyclic_dependencies(const CSV_table& table) const;

private:
	bool has_cyclic_dependencies(
		const CSV_table& table,
		std::unordered_set<CSV_field*>& visited,
		std::unordered_set<CSV_field*>& path,
		const std::shared_ptr<CSV_expression>& expr) const;

	bool visit_subexpr(
		const CSV_table& table,
		std::unordered_set<CSV_field*>& visited,
		std::unordered_set<CSV_field*>& path,
		const std::shared_ptr<CSV_field>& expr) const;
};

