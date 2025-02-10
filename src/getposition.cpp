#include "../headers/getposition.h"
#include <cstdlib>
size_t get_cell(size_t row, size_t col) noexcept {
    // Your implementation here
    // Example return value (adjust logic as needed)
    return row * 9 + col; 
}

size_t get_next_row(size_t row, size_t col) noexcept {
    // Your implementation here
    // Example logic for getting the next row (adjust logic as needed)
    return (col == 8) ? row + 1 : row;
}

size_t get_next_col(size_t col) noexcept {
    // Your implementation here
    // Example logic for getting the next column (adjust logic as needed)
    return (col + 1) % 9;
}
