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

    const std::string& left_column = expr.get()->get_left_column();
    long long left_row = expr.get()->get_left_row();

    const std::string& right_column = expr.get()->get_right_column();
    long long right_row = expr.get()->get_right_row();

    std::shared_ptr<CSV_field> left;
    std::shared_ptr<CSV_field> right;
    try
    {
        left = table.table.at(left_column).at(left_row);
        right = table.table.at(right_column).at(right_row);
    }
    catch (const std::exception&)
    {
        throw std::runtime_error("Incorrect value of one of the fields (a reference to a non-existent field)");
    }

    (*expr).set_left( table.table.at(left_column).at(left_row) );
    (*expr).set_right( table.table.at(right_column).at(right_row) );

    if (visit_subexpr(table, visited, path, (*expr).get_left()))
        return true;

    if (visit_subexpr(table, visited, path, (*expr).get_right()))
        return true;

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

        if (has_cyclic_dependencies(table, visited, path, temp))
            return true;
    }
    else
    {
        visited.insert(expr.get());
    }
    return false;
}