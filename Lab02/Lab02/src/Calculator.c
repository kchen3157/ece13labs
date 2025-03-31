/**
 * @file    Calculator_template.c
 *
 * Add your description here.
 *
 * @author
 *
 * @date
 */
// Standard libraries.
#include <stdio.h>
#include <math.h>

// Course libraries.
// BOARD.h contains useful #defines, e.g. "SUCCESS".
//#include "BOARD.h"


// **** Declare function prototypes here. ****
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
// Add more prototypes below.

int main(void)
{
    CalculatorRun();

    return 0;
}


void CalculatorRun(void)
{
    printf(
        "\n\nWelcome to Kyle's calculator program! Compiled at %s %s\n",
        __DATE__,
        __TIME__
    );
    // Replace this while(1) with your main code loop.

    while (1)
    {
        char operator;
        double operand1, operand2;
        double result;

        scanf("%c", &operator);
        if (operator == '+')
        {
            scanf("%d %d", &operand1, &operand2);
            result = Add(operand1, operand2);
        }
        else if (operator == '-')
        {
            scanf("%d %d", &operand1, &operand2);
            result = Subtract(operand1, operand2);
        }
        else if (operator == '*')
        {
            scanf("%d %d", &operand1, &operand2);
            result = Multiply(operand1, operand2);
        }
        else if (operator == '/')
        {
            scanf("%d %d", &operand1, &operand2);
            result = Divide(operand1, operand2);
        }
        else if (operator == 'c')
        {
            scanf("%d", &operand1);
            result = FahrenheitToCelsius(operand1);
        }
        else if (operator == 'f')
        {
            scanf("%d", &operand1);
            result = CelsiusToFahrenheit(operand1);
        }
        else if (operator == 't')
        {
            scanf("%d", &operand1);
            result = Tangent(operand1);
        }
        else if (operator == 'q')
        {
            return;
        }
        else if (operator == 'r')
        {
            scanf("%d", &operand1);
            result = Round(operand1);
        }
    }

    printf("%f\n", Add(0.9, 0.8));
    printf("%f\n", Subtract(0.9, 0.8));
    printf("%f\n", Multiply(0.9, 0.8));
    printf("%f\n", Divide(0.9, 0.8));
    printf("%f\n", AbsoluteValue(-8.6));
    printf("%f\n", FahrenheitToCelsius(68));
    printf("%f\n", CelsiusToFahrenheit(26));
    printf("%f\n", Average(5, 9));
    printf("%f\n", Tangent(45));
    printf("%f\n", Round(-8.6));
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
    if (operand < 0)
    {
        return operand * -1;
    }
    return operand;
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
    return (int) operand;
}

