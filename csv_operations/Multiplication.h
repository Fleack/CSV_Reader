#pragma once
#include "IOperation.h"

class Multiplication : public IOperation
{
public:
	Multiplication() noexcept;

	~Multiplication();

	long long get_result(const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right) const override;
};