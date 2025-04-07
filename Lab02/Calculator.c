/**
 * @file    Calculator.c
 *
 * My implementation of the Calculator
 *
 * @author Kyle C.
 *
 * @date 2025-04-04
 */

// Standard libraries.
#include <stdio.h>
#include <math.h>

// Course libraries.
// BOARD.h contains useful #defines, e.g. "SUCCESS".
// #include "BOARD.h"

// Function declares
void CalculatorRun(void);

double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double Tangent(double operand);
double Average(double operand1, double operand2);
double Round(double operand);


void CalculatorRun(void)
{
    char operator;
    double operand1, operand2;

    printf(
        "\n\nWelcome to Kyle's calculator program! Compiled at %s %s\n",
        __DATE__,
        __TIME__);

    while (1)
    {
        printf("Type in operator: ");
        scanf(" %c", &operator);

        if (operator== '+') // Addition
        {
            printf("Type in operand 1: ");
            scanf("%lf", &operand1);
            printf("Type in operand 2: ");
            scanf("%lf", &operand2);
            printf("Result of %f + %f: %f\n", operand1, operand2, Add(operand1, operand2));
        }
        else if (operator== '-') // Subtraction
        {
            printf("Type in operand 1: ");
            scanf("%lf", &operand1);
            printf("Type in operand 2: ");
            scanf("%lf", &operand2);
            printf("Result of %f - %f: %f\n", operand1, operand2, Subtract(operand1, operand2));
        }
        else if (operator== '*') // Multiplication
        {
            printf("Type in operand 1: ");
            scanf("%lf", &operand1);
            printf("Type in operand 2: ");
            scanf("%lf", &operand2);
            printf("Result of %f * %f: %f\n", operand1, operand2, Multiply(operand1, operand2));
        }
        else if (operator== '/') // Division
        {
            printf("Type in operand 1: ");
            scanf("%lf", &operand1);
            printf("Type in operand 2: ");
            scanf("%lf", &operand2);
            if (operand2 == 0) // Handle div by 0
            {
                printf("ERROR: Cannot divide by zero!\n");
                continue;
            }
            printf("Result of %f / %f: %f\n", operand1, operand2, Divide(operand1, operand2));
        }
        else if (operator== 'c') // Fahrenheit to Celsius
        {
            printf("Type in operand: ");
            scanf("%lf", &operand1);
            printf("Result of cels(%f): %f\n", operand1, FahrenheitToCelsius(operand1));
        }
        else if (operator== 'f') // Celsius to Fahrenheit
        {
            printf("Type in operand: ");
            scanf("%lf", &operand1);
            printf("Result of fahr(%f): %f\n", operand1, CelsiusToFahrenheit(operand1));
        }
        else if (operator== 't') // Tangent function
        {
            printf("Type in operand: ");
            scanf("%lf", &operand1);
            printf("Result of tan(%f): %f\n", operand1, Tangent(operand1));
        }
        else if (operator== 'q') // Quit
        {
            return;
        }
        else if (operator== 'r') // Round
        {
            printf("Type in operand: ");
            scanf("%lf", &operand1);
            printf("Result of round(%f): %f\n", operand1, Round(operand1));
        }
        else // Default
        {
            printf("Invalid Operator.\n");
        }
    }
}

/*******************************************************************************
 * Define the Add function here.
 ******************************************************************************/
double Add(double operand1, double operand2)
{
    return operand1 + operand2;
}

/*******************************************************************************
 * Define the Subtract function here.
 ******************************************************************************/
double Subtract(double operand1, double operand2)
{
    return operand1 - operand2;
}

/*******************************************************************************
 * Define the Multiply function here.
 ******************************************************************************/
double Multiply(double operand1, double operand2)
{
    return operand1 * operand2;
}

/*******************************************************************************
 * Define the Divide function here.
 ******************************************************************************/
double Divide(double operand1, double operand2)
{
    return operand1 / operand2;
}

/*******************************************************************************
 * Define the Absolute Value function here.
 ******************************************************************************/
double AbsoluteValue(double operand)
{
    return (operand < 0) ? operand * -1 : operand;
}

/*******************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ******************************************************************************/
double FahrenheitToCelsius(double operand)
{
    return (operand - 32.0) * (5.0 / 9.0);
}

/*******************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ******************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    return (operand * (9.0 / 5.0)) + 32.0;
}

/*******************************************************************************
 * Define the Average function here.
 ******************************************************************************/
double Average(double operand1, double operand2)
{
    return (operand1 + operand2) / 2;
}

/*******************************************************************************
 * Define the Tangent function that takes input in degrees.
 ******************************************************************************/
double Tangent(double operand)
{
    return tan(operand * M_PI / 180.0);
}

/*******************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST CORRECTLY utilize
 * this function.
 ******************************************************************************/
double Round(double operand)
{
    if (operand - (int)(operand) >= 0.5)
    {
        return (int)(operand) + 1;
    }
    else if (operand - (int)(operand) <= -0.5)
    {
        return (int)(operand) - 1;
    }
    return (int)(operand);
}
