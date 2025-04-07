/**
 * @file    MatrixMath.c
 *
 * Implementation of functions described in MatrixMath.h
 *
 * @author  Kyle Chen
 *
 * @date    07 Apr 2025
 */

 #include "MatrixMath.h"


 void MatrixPrint(float mat[DIM][DIM])
 {
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            printf("%3.4f\r", mat[i][j]);
        }
        printf("\n");
    }
 }




 int MatrixEquals(float mat1[DIM][DIM], float mat2[DIM][DIM])
 {
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                return 0;
            }
        }
    } 

    return 1;
 }


 void MatrixAdd(float mat1[DIM][DIM], float mat2[DIM][DIM], float result[DIM][DIM])
 {
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
 }

 void MatrixMultiply(float mat1[DIM][DIM], float mat2[DIM][DIM], float result[DIM][DIM])
 {
    for (int mat1_row = 0; mat1_row < DIM; mat1_row++)
    {
        for (int mat2_col = 0; mat2_col < DIM; mat2_col++)
        {
            result[mat1_row][mat2_col] = 0;
            // Sum all products of a row/col pair.
            for (int pos = 0; pos < DIM; pos++)
            {
                result[mat1_row][mat2_col] += mat1[mat1_row][pos] * mat2[mat2_col][pos];
            }
        }
    }
 }

 