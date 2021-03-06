#ifndef MATH_FILE_HANDLER_H
#define MATH_FILE_HANDLER_H

#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>

#define MAX_MATRIX_SIZE 20

bool open_file(FILE** file, char* path);
bool close_file(FILE* file);

#endif // !MATH_FILE_HANDLER_H
