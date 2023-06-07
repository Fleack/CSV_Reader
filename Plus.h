#pragma once
#include "IOperation.h"

class Plus : public IOperation
{
public:
	Plus() noexcept;

	~Plus();

	long long get_result(const CSV_field* left, const CSV_field* right) const noexcept override;
};