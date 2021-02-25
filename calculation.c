#include "calculation.h"
#include <stdlib.h>
#include <math.h>

struct matrix row_echelon_form(struct matrix matrix)
{
	size_t rows = matrix.rows;
	size_t cols = matrix.cols;

	if (rows + 1 != cols)
	{
		printf("\nMatrix must be NxN with vector column free members.");
		struct matrix empty_matrix = { 0, 0, 0, 0 };
		return empty_matrix;
	}

	// to row echelon form
	for (size_t i = 0; i + 1 < matrix.rows; i++)
	{
		swap_max_row(matrix, i);
		for (size_t j = i + 1; j < matrix.rows; j++)
		{
			const double multy = matrix.data[i][i] / matrix.data[j][i];

			for (size_t k = i; k < matrix.cols; k++)
			{
				matrix.data[j][k] = matrix.data[j][k] * multy - matrix.data[i][k];
			}
		}
	}


	// check determinant
	double determinant = 1;
	for (size_t i = 0; i < matrix.rows; i++)
	{
		determinant *= matrix.data[i][i];
	}

	printf("\nDeterminant: %f\n", determinant);
	if (determinant == 0)
	{
		printf("Determinant of matrix equals 0. There may be an infinite number of solutions or no solutions.\n");
		struct matrix empty_matrix = { 0, 0, 0, 0 };
		return empty_matrix;
	}
	
	return matrix;
}


struct answer solve(const struct matrix matrix)
{
	struct answer ans = { .size = matrix.rows, .x = 0};
	ans.x = malloc(sizeof(double) * matrix.rows);

	for (int i = matrix.rows - 1; i >= 0; i--)
	{
		double sum = matrix.data[i][matrix.cols - 1];
		for (int j = i + 1; j < matrix.cols - 1; j++)
		{
			sum -= matrix.data[i][j] * ans.x[j];
		}

		ans.x[i] = sum / matrix.data[i][i];
	}

	return ans;
}

struct answer epsilon(const struct matrix matrix, struct answer ans)
{
	struct answer epsilon = { .size = matrix.rows, .x = 0 };
	epsilon.x = malloc(sizeof(double) * epsilon.size);

	for (size_t i = 0; i < matrix.rows; i++)
	{
		double sum = 0;
		for (size_t j = 0; j < matrix.cols - 1; j++)
		{
			sum += matrix.data[i][j] * ans.x[j];
		}
		double eps = fabs((matrix.data[i][matrix.cols - 1] - sum) / matrix.data[i][matrix.cols - 1]);
		epsilon.x[i] = eps;
	}

	return epsilon;
}

void answer_print(struct answer ans)
{
	printf("\nAnswer:\n");
	for (size_t i = 0; i < ans.size; i++)
	{
		printf("x[%zu] = %0.6f\n", i + 1, ans.x[i]);
	}
}

void epsilon_print(struct answer eps)
{
	printf("\nEpsilon:\n");
	for (size_t i = 0; i < eps.size; i++)
	{
		printf("epsilon[%zu] = %0.16f\n", i + 1, eps.x[i]);
	}
}

void swap_max_row(struct matrix matrix, size_t step)
{
	size_t rows = matrix.rows;
	size_t cols = matrix.cols;


	// Find maximal column and replace it
	// TODO swap rows with every iteration
	size_t max_row = 0;
	size_t start_col = 0;
	double max_size = 0;
	for (size_t i = step; i < rows; i = i + 1)
	{
		if (abs(matrix.data[i][step]) > max_size)
		{
			max_size = matrix.data[i][step];
			max_row = i;
		}
		if (max_size == 0) start_col++;
	}

	for (size_t i = step; i < cols; i = i + 1)
	{
		double temp_data = matrix.data[step][i];
		matrix.data[step][i] = matrix.data[max_row][i];
		matrix.data[max_row][i] = temp_data;
	}
}