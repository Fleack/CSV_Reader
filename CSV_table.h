#pragma once
#include <unordered_map>
#include <memory>

#include "CSV_field.h"

using Table = std::unordered_map< std::string, std::unordered_map< long long, std::shared_ptr<CSV_field> > >;

