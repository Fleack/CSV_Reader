#pragma once
#include "IOperation.h"

class Multiplication : public IOperation
{
public:
	Multiplication() noexcept;

	~Multiplication();

	long long get_result(const CSV_field* left, const CSV_field* right) const noexcept override;
};