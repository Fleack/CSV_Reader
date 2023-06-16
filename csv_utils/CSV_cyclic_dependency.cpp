#include "CSV_cyclic_dependency.h"

CSV_cyclic_dependency::CSV_cyclic_dependency() noexcept = default;

CSV_cyclic_dependency::~CSV_cyclic_dependency() = default;

bool CSV_cyclic_dependency::has_cyclic_dependencies(const CSV_table& table) const
{
    std::unordered_set<CSV_field*> visited;
    std::unordered_set<CSV_field*> path;
    for (auto& i : table.rows)
    {
        for (auto& j : table.header)
        {
            if (j == "") // Column with row numbers
                continue;

            std::shared_ptr<CSV_field> field = nullptr;
            try
            {
                field = table.table.at(j).at(i);
            }
            catch (const std::exception&)
            {
                throw std::runtime_error("Incorrect value of one of the fields (a reference to a non-existent field)");
            }

            if (visited.find(field.get()) != visited.end())
                continue;
            
            if ( std::shared_ptr<CSV_expression> temp = std::dynamic_pointer_cast<CSV_expression> (field) )
            {
                if (has_cyclic_dependencies(table, visited, path, temp))
                    return true;
            }
            else
            {
                visited.insert(field.get());
            }
        }
    }
    return false;
}

bool CSV_cyclic_dependency::has_cyclic_dependencies(
    const CSV_table& table,
    std::unordered_set<CSV_field*>& visited,
    std::unordered_set<CSV_field*>& path,
    const std::shared_ptr<CSV_expression>& expr) const
{
    visited.insert(expr.get());
    path.insert(expr.get());

    const std::string& left_operand = (*expr).get_left_operand();
    std::shared_ptr<CSV_field> left;
    if (!is_number(left_operand))
    {
        left = get_subfield(table, visited, path, expr, left_operand);

        if (visit_subexpr(table, visited, path, left))
            return true;
    }
    else
    {
        left = std::make_shared<CSV_operation_number>(std::stoll(left_operand));
    }

    if ((*expr).get_left().get() == nullptr)
        (*expr).set_left(left);

    const std::string& right_operand = (*expr).get_right_operand();
    std::shared_ptr<CSV_field> right;
    if (!is_number(right_operand))
    {
        right = get_subfield(table, visited, path, expr, right_operand);

        if (visit_subexpr(table, visited, path, right))
            return true;
    }
    else
    {
        right = std::make_shared<CSV_operation_number>(std::stoll(right_operand));
    }

    if ((*expr).get_right().get() == nullptr)
        (*expr).set_right(right);

    path.erase(expr.get());
    return false;
}

bool CSV_cyclic_dependency::visit_subexpr(
    const CSV_table& table,
    std::unordered_set<CSV_field*>& visited,
    std::unordered_set<CSV_field*>& path,
    const std::shared_ptr<CSV_field>& expr) const
{
    if (std::shared_ptr<CSV_expression> temp = std::dynamic_pointer_cast<CSV_expression> (expr))
    {
        if (path.find(temp.get()) != path.end())
            return true;

        if (visited.find(temp.get()) != visited.end())
            return false;

        if (has_cyclic_dependencies(table, visited, path, temp))
            return true;
    }
    else
    {
        visited.insert(expr.get());
    }
    return false;
}

std::shared_ptr<CSV_field> CSV_cyclic_dependency::get_subfield(
    const CSV_table& table,
    std::unordered_set<CSV_field*>& visited,
    std::unordered_set<CSV_field*>& path,
    const std::shared_ptr<CSV_field>& expr,
    const std::string& operand) const
{
    std::pair<std::string, long long> temp = parse_operand(operand);
    std::string column = temp.first;
    long long row = temp.second;
    std::shared_ptr<CSV_field> op_ptr;

    try
    {
        op_ptr = table.table.at(column).at(row);
    }
    catch (const std::exception&)
    {
        throw std::runtime_error("Incorrect value of one of the fields (a reference to a non-existent field)");
    }

    return op_ptr;
}