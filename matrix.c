#include "matrix.h"
#include <malloc.h>
#include <stdbool.h>
#include <ctype.h>

#define DEFAULT_COEF 1

static void fill_matrix(struct matrix* matrix);
static int64_t check_coefficient(const char* buffer);

struct matrix matrix_create(size_t rows, size_t cols, int64_t coef)
{
	struct matrix matrix;
	matrix.rows = rows;
	matrix.cols = cols;
	matrix.coef = coef;
	matrix.data = malloc(rows * sizeof(double*));

	for (size_t i = 0; i < rows; i = i + 1)
	{
		matrix.data[i] = malloc(sizeof(double) * cols);
	}

	return matrix;
}

struct matrix read_matrix_file(FILE* file)
{
	printf("Reading matrix from file:\n");
	char   buffer[1024];
	size_t nbytes;
	while ((nbytes = fread(buffer, sizeof(char), sizeof(buffer), file)) != 0)
		fwrite(buffer, sizeof(char), nbytes, stdout);


	fseek(file, 0, SEEK_SET); // ÏÐÎ×ÈÒÀÒÜ ÏÅÐÂÓÞ ÑÒÐÎÊÓ ÔÀÉËÀ È ÄÎÑÒÀÒÜ ÊÎÝÔ.
	int64_t coef = check_coefficient(buffer);

	size_t file_read_pos = 0;
	if (coef != 1)
	{
		while (buffer[file_read_pos] != '\n') file_read_pos++;
		file_read_pos++;					// next pos after '\n'
	}

	size_t rows = rows_in_matrix(buffer, file_read_pos);
	size_t cols = cols_in_matrix(buffer, rows);

	if (rows > 20 || cols > 20)
	{
		printf("Invalid source file. Max size of matrix is 20x20.\n");
		struct matrix matrix = { 0, 0, 0 };
		return matrix;
	}

	if (coef <= 0)
	{
		printf("Coefficient must be >= 1. Please try again.\n");
		struct matrix matrix = { 0, 0, 0, 0 };		// empty matrix
		return matrix;
	}

	struct matrix matrix = matrix_create(rows, cols, coef);


	fseek(file, file_read_pos, SEEK_SET);
	for (size_t i = 0; i < rows; i = i + 1)
	{
		for (size_t j = 0; j < cols; j = j + 1)
		{
			double num;
			if (fscanf(file, "%lf", &num) > 0)
				matrix.data[i][j] = num;
		}
	}

	return matrix;
}

struct matrix read_matrix_input()
{
	size_t rows;
	printf("Enter matrix rows amount: ");
	scanf_s("%zu", &rows);

	size_t cols;
	printf("Enter matrix columns amount (with vector column free member): ");
	scanf_s("%zu", &cols);

	int64_t coef;
	printf("Enter coefficient of matrix: ");
	scanf_s("%"SCNd64, &coef);

	printf("Enter matrix: \n");

	if (rows > 20 || cols > 20)
	{
		printf("Max size of matrix is 20x20. Please try again.\n");
		struct matrix matrix = { 0, 0, 0, 0 };		// empty matrix
		return matrix;
	}

	if (coef <= 0)
	{
		printf("Coefficient must be >= 1. Please try again.\n");
		struct matrix matrix = { 0, 0, 0, 0 };		// empty matrix
		return matrix;
	}

	struct matrix matrix = matrix_create(rows, cols, coef);
	fill_matrix(&matrix);

	return matrix;
}

void matrix_print(const struct matrix matrix)
{
	printf("Matrix coefficient: %"PRId64"\n", matrix.coef);
	for (size_t i = 0; i < matrix.rows; i = i + 1)
	{
		for (size_t j = 0; j < matrix.cols; j = j + 1)
		{
			printf("%0.2f ", matrix.data[i][j]);
		}
		printf("\n");
	}
}

struct matrix matrix_copy(const struct matrix matrix)
{
	struct matrix new_matrix = matrix_create(matrix.rows, matrix.cols, matrix.coef);

	for (size_t i = 0; i < matrix.rows; i++)
	{
		for (size_t j = 0; j < matrix.cols; j++)
		{
			new_matrix.data[i][j] = matrix.data[i][j];
		}
	}

	return new_matrix;
}

void matrix_free(struct matrix* matrix)
{
	matrix->rows = 0;
	matrix->cols = 0;
	matrix->coef = 0;
	free(matrix->data);
}

size_t cols_in_matrix(const char* row, size_t rows)
{
	size_t counted = 0;
	const char* it = row;
	size_t inword = 0;

	do switch (*it) {
	case '\0':
	case ' ': case '\t': case '\n': case '\r': // TODO others?
		if (inword) { inword = 0; counted++; }
		break;
	default: inword = 1;
	} while (*it++);

	return counted / rows;
}

size_t rows_in_matrix(const char* buffer, size_t buffer_pointer)
{
	size_t rows = 1;
	bool already_newline = false;
	for (size_t i = buffer_pointer; i < 1024 - 1; i++)
	{
		if (buffer[i] == '\n' && !already_newline)
		{
			already_newline = true;
			rows++;
		}

		if (buffer[i] >= '0' || buffer[i] <= '9') already_newline = false;
	}
	
	return rows;
}

static void fill_matrix(struct matrix* matrix)
{
	for (size_t i = 0; i < matrix->rows; i = i + 1)
	{
		for (size_t j = 0; j < matrix->cols; j = j + 1)
		{
			double num;
			if (scanf_s("%lf", &num) > 0)
				matrix->data[i][j] = num;
		}
	}
}

static int64_t check_coefficient(const char* buffer)
{
	bool already_num = false;
	bool already_whitespace = false;
	bool need_num = false;

	size_t number_position = 0;
	size_t buffer_size = 0;
	while (buffer[buffer_size] != '\n')
	{
		if ((buffer[buffer_size] == ' ' || buffer[buffer_size] == '\r' || buffer[buffer_size] == '\t') && already_num)
		{
			already_whitespace = true;
		}
		if (isdigit(buffer[buffer_size]))
		{
			if (!already_whitespace)
			{
				if (!already_num) number_position = buffer_size;
				already_num = true;
				need_num = true;
			}
			if (already_whitespace && already_num)
			{
				need_num = false;
				break;
			}
		}

		buffer_size++;
	}

	if (need_num)
	{
		char* temp_array = malloc(sizeof(char) * buffer_size);
		for (size_t i = 0; i < buffer_size - number_position; i = i + 1)
		{
			temp_array[i] = buffer[number_position + i];
		}

		int64_t num = 0;
		sscanf(temp_array, "%"SCNd64, &num);
		free(temp_array);
		return num;
	}

	return DEFAULT_COEF;
}