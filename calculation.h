#ifndef MATH_CALCULATION_H
#define MATH_CALCULATION_H

#include "matrix.h"

struct answer
{
	size_t size;
	double* x;
};

struct matrix row_echelon_form(const struct matrix source_matrix);
struct answer solve(const struct matrix row_echelon_matrix);
struct answer epsilon(const struct matrix, struct answer x);
void answer_print(struct answer);
void epsilon_print(struct answer eps);

void swap_max_row(struct matrix matrix, size_t step);

#endif // !MATH_CALCULATION_H
