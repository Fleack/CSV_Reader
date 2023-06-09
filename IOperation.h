#pragma once
#include <memory>

#include "CSV_field.h"

class IOperation
{
public:
	IOperation() = default;

	virtual ~IOperation() = default;

	virtual long long get_result(const std::shared_ptr<CSV_field>& left, const std::shared_ptr<CSV_field>& right) const = 0;
};