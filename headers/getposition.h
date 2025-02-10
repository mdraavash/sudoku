#ifndef GETPOSITION_H
#define GETPOSITION_H

#include <cstddef> // For size_t

size_t get_cell(size_t row, size_t col) noexcept;
size_t get_next_row(size_t row, size_t col) noexcept;
size_t get_next_col(size_t col) noexcept;

#endif
