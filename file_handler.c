#include "file_handler.h"
#include "matrix.h"
#include "utils.h"
#include <malloc.h>

#define READ_MODE "rb"
#define NUM_SIZE 100


bool open_file(FILE** file, char* path)
{
	if (*file == NULL) return false;
	if (path == NULL) return false;
	*file = fopen(path, READ_MODE);
	if (*file == NULL) return false;

	return true;
}


bool close_file(FILE* file)
{
	if (file == NULL) return false;
	if (fclose(file) != 0) return false;

	return true;
}