#include "CSV_utilfunc.h"

bool is_digit(char c) noexcept
{
    return c >= '0' && c <= '9';
}

bool is_number(const std::string& str) noexcept
{
    if (str.size() == 0)
        return false;

    size_t start = 0;

    if (str[0] == '-')
        start = 1;

    for (size_t i = start; i < str.size(); i++)
    {
        if (!is_digit(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool is_letter(char c) noexcept
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool is_string(const std::string& str) noexcept
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

bool is_operator(char c) noexcept
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

std::pair<std::string, long long> parse_operand(const std::string& operand) noexcept
{
    std::string column = "";
    size_t i = 0;
    for (; i < operand.size(); i++)
    {
        if (is_letter(operand[i]))
            column += operand[i];
        else
            break;
    }

    std::string row = "";
    for (; i < operand.size(); i++)
    {
        row += operand[i];
    }

    return std::make_pair(column, std::stoll(row));
}