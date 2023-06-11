#pragma once
#include <string>

bool is_digit(char c) noexcept;

bool is_number(const std::string& str) noexcept;

bool is_letter(char c) noexcept;

bool is_string(const std::string& str) noexcept;

bool is_operator(char c) noexcept;

std::pair<std::string, long long> parse_operand(const std::string& operand) noexcept;