#pragma once
#include "IOperation.h"

class Division : public IOperation
{
public:
	Division() noexcept;

	~Division();

	long long get_result(const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right) const noexcept override;
};