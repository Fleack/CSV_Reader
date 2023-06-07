#pragma once
#include "CSV_field.h"

class IOperation
{
public:
	IOperation() = default;

	virtual ~IOperation() = default;

	virtual long long get_result(const CSV_field* left, const CSV_field* right) const = 0;
};