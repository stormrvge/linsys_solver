#include <stdio.h>
#include "file_handler.h"
#include "matrix.h"
#include "calculation.h"

int main(int argc, char** argv)
{
    struct matrix input_matrix;

    if (argc == 1)
    {
        input_matrix = read_matrix_input();
    }
    else if (argc == 2)
    {
        FILE* txt_file;
        open_file(&txt_file, argv[1]);
        input_matrix = read_matrix_file(txt_file);
    }
    else
    {
        printf("./linsys-solver path_to_matrix.txt OR ./linsys-solver");
        return 2;
    }
    
    struct matrix echelon_matrix = matrix_copy(input_matrix);
    row_echelon_form(echelon_matrix);

    if (echelon_matrix.cols == 0 || echelon_matrix.rows == 0 || echelon_matrix.coef == 0) return 1;     // if bad matrix
    else
    {
        printf("\nRow echelon form of input matrix\n");
        matrix_print(echelon_matrix);

        struct answer ans = solve(echelon_matrix);
        answer_print(ans);

        struct answer eps = epsilon(input_matrix, ans);
        epsilon_print(eps);


        free(ans.x);
        free(eps.x);

        matrix_free(&input_matrix);
        matrix_free(&echelon_matrix);
        return 0;
    }
}