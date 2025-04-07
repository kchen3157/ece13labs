/*
 * @file    Lab2_main.c
 *
 * Math is fun!!
 *
 * @author  HARE Lab
 * @author  jLab
 * @version 1.0.0
 *
 * @date 13 Aug 2024.
 */
// Standard libraries.
#include <stdio.h>
#include <math.h>


// CalculatorRun() prototype.
void CalculatorRun(void);

int main(void)
{
    CalculatorRun();

    printf(
        "Calculator has exited; "
        "please restart to perform more calculations.\r\n"
    );
    while(1);
}

