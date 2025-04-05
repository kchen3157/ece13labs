/**
 * @file    Calculator.h
 *
 * Header File to use Calculator.c
 *
 * @author Kyle C.
 *
 * @date 2025-04-04
 */

#ifndef __CALCULATOR_H__

#define __CALCULATOR_H__

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

#endif // __CALCULATOR_H__
