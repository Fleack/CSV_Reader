#pragma once
#include "IOperation.h"

class Plus : public IOperation
{
public:
	Plus() noexcept;

	~Plus();

	long long get_result(const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right) const noexcept override;
};