cmake_minimum_required(VERSION 3.12)
project(CSV_Reader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_COMPILER "C:/Users/melni/gcc/bin/g++.exe")

set(csv_fields_sources
    csv_fields/CSV_expression.cpp
    csv_fields/CSV_field.cpp
	csv_fields/CSV_operation_number.cpp
    csv_fields/CSV_value.cpp
)

set(csv_fields_headers
    csv_fields/CSV_expression.h
    csv_fields/CSV_field.h
	csv_fields/CSV_operation_number.h
    csv_fields/CSV_value.h
)

set(csv_operations_sources
	csv_operations/Division.cpp
    csv_operations/Minus.cpp
    csv_operations/Multiplication.cpp
    csv_operations/Plus.cpp
)

set(csv_operations_headers
    csv_operations/Division.h
    csv_operations/IOperation.h
    csv_operations/Minus.h
    csv_operations/Multiplication.h
    csv_operations/Plus.h
)

set(csv_utils_sources
    csv_utils/CSV_cyclic_dependency.cpp
    csv_utils/CSV_parser.cpp
    csv_utils/CSV_reader.cpp
	csv_utils/CSV_utilfunc.cpp
)

set(csv_utils_headers
    csv_utils/CSV_cyclic_dependency.h
    csv_utils/CSV_parser.h
    csv_utils/CSV_reader.h
    csv_utils/CSV_table.hpp
	csv_utils/CSV_utilfunc.h
)

add_executable(CSV_Reader
    CSV.h
    main.cpp
    ${csv_fields_sources}
    ${csv_fields_headers}
    ${csv_operations_sources}
    ${csv_operations_headers}
    ${csv_utils_sources}
    ${csv_utils_headers}
)

target_include_directories(CSV_Reader PRIVATE
    csv_fields
    csv_operations
    csv_utils
)