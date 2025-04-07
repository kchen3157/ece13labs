/**
 * @file    MatrixMath.c
 *
 * Implementation of functions described in MatrixMath.h
 *
 * @author  Kyle Chen
 *
 * @date    07 Apr 2025
 */


#include <stdio.h>
#include <math.h>


#include "MatrixMath.h"




void MatrixPrint(float mat[DIM][DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            printf("%08.4f\t", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int MatrixEquals(float mat1[DIM][DIM], float mat2[DIM][DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            if (fabs(mat1[i][j] - mat2[i][j]) > FP_DELTA)
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
                result[mat1_row][mat2_col] += mat1[mat1_row][pos] * mat2[pos][mat2_col];
            }
        }
    }
}

void MatrixScalarAdd(float x, float mat[DIM][DIM], float result[DIM][DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            result[i][j] = mat[i][j] + x;
        }
    }
}

void MatrixScalarMultiply(float x, float mat[DIM][DIM], float result[DIM][DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            result[i][j] = mat[i][j] * x;
        }
    }
}

float MatrixTrace(float mat[DIM][DIM])
{
    float trace = 0;
    for (int i = 0; i < DIM; i++)
    {
        trace += mat[i][i];
    }
    return trace;
}

void MatrixTranspose(float mat[DIM][DIM], float result[DIM][DIM])
{
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            result[i][j] = mat[j][i];
        }
    }
}

void MatrixSubmatrix(int i, int j, float mat[DIM][DIM], float result[DIM - 1][DIM - 1])
{
    for (int mat_row = 0, res_row = 0; mat_row < DIM && res_row < (DIM - 1); mat_row++)
    {
        if (mat_row != i)
        {
            for (int mat_col = 0, res_col = 0; mat_col < DIM && res_col < (DIM - 1); mat_col++)
            {
                if (mat_col != j)
                {
                    result[res_row][res_col] = mat[mat_row][mat_col];
                    res_col++;
                }
            }
            res_row++;
        }
    }
}

float MatrixDeterminant(float mat[DIM][DIM])
{
    // Generate vector of signs for first row
    int signs[DIM];
    for (int i = 0; i < DIM; i++)
    {
        signs[i] = (i % 2 == 0) ? 1 : -1;
    }

    float result = 0;
    for (int col = 0; col < DIM; col++)
    {
        // Sum of minor determinants
        float minor[DIM - 1][DIM - 1];
        MatrixSubmatrix(0, col, mat, minor);
        result += signs[col] * mat[0][col] * (minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0]);
    }

    return result;
}

void MatrixInverse(float mat[DIM][DIM], float result[DIM][DIM])
{
    // get cofactor matrix
    float mat_cof[DIM][DIM];
    float temp[DIM - 1][DIM - 1];
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            MatrixSubmatrix(i, j, mat, temp);
            mat_cof[i][j] = temp[0][0] * temp[1][1] - temp[0][1] * temp[1][0];
        }
    }


    float mat_transposed[DIM][DIM];
    
    MatrixTranspose(mat_cof, mat_transposed);

    // Apply signs to transposed matrix
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            if ((i + j) % 2 != 0)
            {
                mat_transposed[i][j] *= -1;
            }
        }
    }
        
    MatrixScalarMultiply(1 / MatrixDeterminant(mat), mat_transposed, result);
}
