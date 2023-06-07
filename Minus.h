#pragma once
#include "IOperation.h"

class Minus : public IOperation
{
public:
	Minus() noexcept;

	~Minus();

	long long get_result(const CSV_field* left, const CSV_field* right) const noexcept override;
};