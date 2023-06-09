#pragma once
#include <unordered_set>

#include "CSV_table.h"
#include "CSV_expression.h"

class CSV_cyclic_dependency
{
public:

	CSV_cyclic_dependency() noexcept;

	~CSV_cyclic_dependency();

	bool has_cyclic_dependencies(
		const Table& table,
		const std::vector<std::string>& header,
		const std::vector<long long>& rows) const noexcept;

private:
	bool has_cyclic_dependencies(
		const Table& table,
		std::unordered_set<CSV_field*>& visited,
		std::unordered_set<CSV_field*>& path,
		const std::shared_ptr<CSV_expression>& expr) const noexcept;

	bool visit_subexpr(const Table& table,
		std::unordered_set<CSV_field*>& visited,
		std::unordered_set<CSV_field*>& path,
		const std::shared_ptr<CSV_field>& expr) const noexcept;
};

