/**
 * @file mml_test_template.c
 * 
 * Test suite for MatrixMath.c
 *
 * @author Kyle Chen
 *
 * @date 2025-04-07
 */
// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>

// User libraries:
#include "MatrixMath.h"

// Module-level variables:
float zero_matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
float id_matrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
float max_matrix[3][3] = {{999.0, 999.0, 999.0}, {999.0, 999.0, 999.0}, {999.0, 999.0, 999.0}};
float min_matrix[3][3] = {{999.0, -999.0, -999.0}, {999.0, -999.0, -999.0}, {-999.0, -999.0, -999.0}};

float test_matrix_1[3][3] = {{4, 8, 2}, {1, 9, 7}, {1, 4, 8}};
float test_matrix_2[3][3] = {{8, 5, 4}, {3, 3, 7}, {6, 0, 2}};
float test_matrix_3[3][3] = {{68, 44, 76}, {77, 32, 81}, {68, 17, 48}};                                                   // test_matrix_1 * test_matrix_2
float test_matrix_4[3][3] = {{16, 32, 8}, {4, 36, 28}, {4, 16, 32}};                                                      // test_matrix_1 * 4
float test_matrix_5[3][3] = {{12, 13, 6}, {4, 12, 14}, {7, 4, 10}};                                                       // test_matrix_1 + test_matrix_2
float test_matrix_6[3][3] = {{9, 13, 7}, {6, 14, 12}, {6, 9, 13}};                                                        // test_matrix_1 + 5
float test_matrix_7[3][3] = {{0.27848, -0.35443, 0.24050}, {-0.00632, 0.18987, -0.16455}, {-0.03164, -0.05063, 0.17721}}; // test_matrix^-1
float test_matrix_8[3][3] = {{4, 1, 1}, {8, 9, 4}, {2, 7, 8}};                                                            // trans(test_matrix)

int main(void)
{
    // Temporary matrix to store function results
    float temp[3][3];

    // Test MatrixPrint()  
    printf(
        "Beginning CRUZID's mml test harness, compiled on %s %s\n",
        __DATE__,
        __TIME__);

    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(id_matrix);
    MatrixPrint(max_matrix);
    MatrixPrint(min_matrix);
    MatrixPrint(test_matrix_1);

    // Test MatrixEquals()
    if (!(MatrixEquals(test_matrix_1, test_matrix_1)))
    {
        printf("Test 1 MatrixEquals() failed\n");
        return -1;
    }
    if (MatrixEquals(test_matrix_1, zero_matrix))
    {
        printf("Test 2 MatrixEquals() failed\n");
        return -1;
    }
    printf("All MatrixEquals() tests passed.\n");

    // Test MatrixMultiply()
    MatrixMultiply(test_matrix_1, test_matrix_2, temp);
    if (!(MatrixEquals(test_matrix_3, temp)))
    {
        printf("Test 1 MatrixMultiply() failed\n");
        return -1;
    }
    MatrixMultiply(test_matrix_2, test_matrix_1, temp);
    if ((MatrixEquals(test_matrix_3, temp)))
    {
        printf("Test 2 MatrixMultiply() failed\n");
        return -1;
    }
    MatrixMultiply(test_matrix_1, zero_matrix, temp);
    if (!(MatrixEquals(zero_matrix, temp)))
    {
        printf("Test 3 MatrixMultiply() failed\n");
        return -1;
    }
    printf("All MatrixMultiply() tests passed.\n");

    // Test MatrixScalarMultiply()
    MatrixScalarMultiply(0, test_matrix_1, temp);
    if (!(MatrixEquals(zero_matrix, temp)))
    {
        printf("Test 1 MatrixScalarMultiply() failed\n");
        return -1;
    }
    MatrixScalarMultiply(4, test_matrix_1, temp);
    if (!(MatrixEquals(test_matrix_4, temp)))
    {
        printf("Test 2 MatrixScalarMultiply() failed\n");
        return -1;
    }
    printf("All MatrixScalarMultiply() tests passed.\n");

    // Test MatrixDeterminant()
    if (MatrixDeterminant(test_matrix_1) != 158)
    {
        printf("Test 1 MatrixDeterminant() failed\n");
        return -1;
    }
    if (MatrixDeterminant(zero_matrix) != 0)
    {
        printf("Test 2 MatrixDeterminant() failed\n");
        return -1;
    }
    printf("All MatrixDeterminant() tests passed.\n");

    // Test MatrixAdd()
    MatrixAdd(test_matrix_1, zero_matrix, temp);
    if (!(MatrixEquals(test_matrix_1, temp)))
    {
        printf("Test 1 MatrixAdd() failed\n");
        return -1;
    }
    MatrixAdd(test_matrix_1, test_matrix_2, temp);
    if (!(MatrixEquals(temp, test_matrix_5)))
    {
        printf("Test 2 MatrixAdd() failed\n");
        return -1;
    }
    MatrixAdd(test_matrix_2, test_matrix_1, temp);
    if (!(MatrixEquals(temp, test_matrix_5)))
    {
        printf("Test 3 MatrixAdd() failed\n");
        return -1;
    }
    printf("All MatrixAdd() tests passed.\n");

    // Test MatrixScalarAdd()
    MatrixScalarAdd(0, test_matrix_1, temp);
    if (!(MatrixEquals(test_matrix_1, temp)))
    {
        printf("Test 1 MatrixScalarAdd() failed\n");
        return -1;
    }
    MatrixScalarAdd(5, test_matrix_1, temp);
    if (!(MatrixEquals(test_matrix_6, temp)))
    {
        printf("Test 2 MatrixScalarAdd() failed\n");
        return -1;
    }
    printf("All MatrixScalarAdd() tests passed.\n");

    // Test MatrixInverse()
    MatrixInverse(test_matrix_1, temp); // M1^-1 = M7
    if (!(MatrixEquals(test_matrix_7, temp)))
    {
        printf("Test 1 MatrixInverse() failed\n");
        return -1;
    }
    MatrixInverse(temp, temp); // M1^-1^-1 = M1
    if (!(MatrixEquals(test_matrix_1, temp)))
    {   
        printf("Test 2 MatrixInverse() failed\n");
        return -1;
    }
    MatrixInverse(id_matrix, temp); // I^-1 = I
    if (!(MatrixEquals(id_matrix, temp)))
    {
        printf("Test 3 MatrixInverse() failed\n");
        return -1;
    }
    printf("All MatrixInverse() tests passed.\n");

    // Test MatrixTranspose()
    MatrixTranspose(id_matrix, temp);
    if (!(MatrixEquals(id_matrix, temp)))
    {
        printf("Test 1 MatrixTranspose() failed\n");
        return -1;
    }
    MatrixTranspose(test_matrix_1, temp);
    if (!(MatrixEquals(test_matrix_8, temp)))
    {
        printf("Test 2 MatrixTranspose() failed\n");
        return -1;
    }
    MatrixTranspose(test_matrix_8, temp);
    if (!(MatrixEquals(test_matrix_1, temp)))
    {
        printf("Test 3 MatrixTranspose() failed\n");
        return -1;
    }
    printf("All MatrixTranspose() tests passed.\n");

    // Test MatrixTrace()
    if (!(MatrixTrace(id_matrix) == DIM))
    {
        printf("Test 1 MatrixTrace() failed\n");
        return -1;
    }
    if (!(MatrixTrace(test_matrix_1) == 21))
    {
        printf("Test 2 MatrixTrace() failed\n");
        return -1;
    }
    printf("All MatrixTrace() tests passed.\n");

    return 0;
}
