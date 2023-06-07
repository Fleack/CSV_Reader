#pragma once
#include "IOperation.h"

class Division : public IOperation
{
public:
	Division() noexcept;

	~Division();

	long long get_result(const CSV_field* left, const CSV_field* right) const noexcept override;
};