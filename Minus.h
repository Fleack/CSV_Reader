#pragma once
#include "IOperation.h"

class Minus : public IOperation
{
public:
	Minus() noexcept;

	~Minus();

	long long get_result(const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right) const noexcept override;
};