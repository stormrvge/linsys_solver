#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include <inttypes.h>
#include <stdio.h>

struct matrix
{ 
	size_t rows;
	size_t cols;
	int64_t coef;
	double** data;
};

struct matrix matrix_create(size_t rows, size_t cols, int64_t coef);
struct matrix read_matrix_file(FILE* file);
struct matrix read_matrix_input();

void matrix_print(const struct matrix);
struct matrix matrix_copy(const struct matrix);
void matrix_free(struct matrix* matrix);

size_t cols_in_matrix(const char* row, size_t rows);
size_t rows_in_matrix(const char* buffer, size_t buffer_pointer);

#endif // !MATH_MATRIX_H
