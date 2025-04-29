/**
 * @file    rpn_test.c
 *
 * @author
 *
 * @date
 */
// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Course library.
#include "BOARD.h"

// User libraries.
#include "rpn.h"


#define NUM_SIMPLE_CASES 8
#define NUM_F_CASES 8
#define NUM_COMPLEX_CASES 5
#define NUM_ERROR_CASES 14
#define NUM_PROCESS_BKSPCE_CASES 8

#define MID_STR_LEN 70
#define MAX_STR_LEN 256


//* Test case / expected value data

// Simple: Ints and single operations
char simple_test_cases[NUM_SIMPLE_CASES][MID_STR_LEN] = {"1 1 +", "7 8 +", "9 4 *", "5 6 *", 
    "64 8 /", "81 3 /", "7 1 -", "4 2 -"};
double simple_test_results[NUM_SIMPLE_CASES] = {2, 15, 36, 30, 8, 27, 6, 2};

// Float: Floats and single operations
char f_test_cases[NUM_F_CASES][MID_STR_LEN] = {"1.89 1.13 +", "7.23 8.63 +", 
    "9.36 4.75 *", "5.42 6.72 *", 
    "64.11 8.27 /", "82.60 3.34 /", 
    "7.61 1.36 -", "4.45 2.26 -"};
double f_test_results[NUM_F_CASES] = {3.02, 15.86, 44.46, 36.4224, 7.752116, 24.730539, 6.25, 2.19};

// Complex: >1 operation, multiple 
char complex_test_cases[NUM_COMPLEX_CASES][MID_STR_LEN] = {"8 8.2 + 4 * 7 -", "8 6 2.34 89.3 74.3 / / - +", 
    "92 31.13 / 23 + 4.2 83 / /", "8 3 * 62.3 / 72.38 +",
    "74.23 74 8 0 7238 74 + + / - *"};
double complex_test_results[NUM_COMPLEX_CASES] = {57.8, 12.053057, 512.927126, 72.765233, 5492.938786};

// Error: All should generate some type of error.
char error_test_cases[NUM_ERROR_CASES][MID_STR_LEN] = {"4 0 /", "74.23 74 8 0 7238 74 + / / - *",  //RPN_ERROR_DIVIDE_BY_ZERO
                                "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1", //RPN_ERROR_STACK_OVERFLOW
                                "9 9 9 9 9 9 9 9 9 9 + 9 9 9 9 9 - 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9", //RPN_ERROR_STACK_OVERFLOW
                                "8 97 / + *", "7 /", "", "*", "8 3 * 62.3 / 72.38 + -", "8 - - -", //RPN_ERROR_TOO_FEW_ITEMS_REMAIN
                                "8 7 6 +", "74.23 74 8 0 7238 74 + + /", //RPN_ERROR_TOO_MANY_ITEMS_REMAIN
                                "8 7 f", "783 73 627 / 87.3 + 84 k /"}; //RPN_ERROR_INVALID_TOKEN
int error_test_results[NUM_ERROR_CASES] = {RPN_ERROR_DIVIDE_BY_ZERO, RPN_ERROR_DIVIDE_BY_ZERO,
                                RPN_ERROR_STACK_OVERFLOW, RPN_ERROR_STACK_OVERFLOW,
                                RPN_ERROR_TOO_FEW_ITEMS_REMAIN, RPN_ERROR_TOO_FEW_ITEMS_REMAIN,
                                RPN_ERROR_TOO_FEW_ITEMS_REMAIN, RPN_ERROR_TOO_FEW_ITEMS_REMAIN,
                                RPN_ERROR_TOO_FEW_ITEMS_REMAIN, RPN_ERROR_TOO_FEW_ITEMS_REMAIN,
                                RPN_ERROR_TOO_MANY_ITEMS_REMAIN, RPN_ERROR_TOO_MANY_ITEMS_REMAIN,
                                RPN_ERROR_INVALID_TOKEN, RPN_ERROR_INVALID_TOKEN};

// ProcessBackspaces testcases
char process_backspaces_test_cases[NUM_PROCESS_BKSPCE_CASES][MAX_STR_LEN] = 
        {("uah238jdoa83j38ru83rxo87ufhow48rmxho847fhmo4qeufhauihfuisasdkdjkd"
        "fjaiodsjfidhfujuairjuaiwhf8hfq4o8r88q7yr8oq389rsuq38radifjaiosjdfioajodjfliajjifjeifjeifjdksjdoasdfjlaidjfladjfaidjfliajdf"
        "9yq28yr8ruajdsiujfajaisodjiosjdfiuh\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"),
        "83492\b\b\b83928\b\b", "ha8jefauihed\biaej\bha\bfdsu\b\b\b\bfdusi\b\b", "\n\n\n\b\b\bjeif\b\b\b\b",
        ("iajifjiwejfhqiu3hefaoiuwhesofuhaouesfoaluwe\bfjoaeocubaoufhoaeufdjoauehdoauehad\behdoauehdoaeudhaouefuae"
        "jaifjaiheuhfaouwesdj\buwehnoauehjfdoauliedjeoaiunoau\bedjailuwjesdoailuweshajluhdou\b\blsdjauedjeludhadh"),
        "8\b", "jdijfaiodsjf\b\b\b\bjdifjaisjddoifja", "jeijijfqiewfiuqhduhefuqejdujedioquh\b\b\b\b\b"};

char process_backspaces_test_results[NUM_PROCESS_BKSPCE_CASES][MAX_STR_LEN] = 
        {("uah238jdoa83j38ru83rxo87ufhow48rmxho847fhmo4qeufhauihfuisasdkdjkd"
        "fjaiodsjfidhfujuairjuaiwhf8hfq4o8r88q7yr8oq389rsuq38radifjaiosjdfioajodjfliajjifjeifjeifjdksjdoasdfjlaidjfladjfaidjfliajdf"
        "9y"), "83839", "ha8jefauiheiaehfdu", "",
        ("iajifjiwejfhqiu3hefaoiuwhesofuhaouesfoaluwfjoaeocubaoufhoaeufdjoauehdoauehaehdoauehdoaeudhaouefuae"
        "jaifjaiheuhfaouwesduwehnoauehjfdoauliedjeoaiunoaedjailuwjesdoailuweshajluhdlsdjauedjeludhadh"),
        "", "jdijfaiojdifjaisjddoifja", "jeijijfqiewfiuqhduhefuqejdujed"};

void ProcessBackspacesTestPrint(char* test_string);

int
main(void)
{
    BOARD_Init();

    printf("\n###### Beginning CRUZID's rpn test harness: ####\n\n");

    //* test simple testcases
    double temp;
    for (int i = 0; i < 8; i++)
    {
        printf("Testing RPN_Evaluate with \"%s\"... \n ", simple_test_cases[i]);
        if (RPN_Evaluate(simple_test_cases[i], &temp) != RPN_NO_ERROR)
        {
            printf("\tFailed, RPN_Evaluate produced an error\n");
        }
        else if (temp != simple_test_results[i])
        {
            printf("\tFailed, expected = %f , result = %f\n", simple_test_results[i], temp);
        }
        else
        {
            printf("   Success!\n");
        }
    }

    //* test float testcases
    for (int i = 0; i < 8; i++)
    {
        printf("Testing RPN_Evaluate with \"%s\"... \n ", f_test_cases[i]);
        if (RPN_Evaluate(f_test_cases[i], &temp) != RPN_NO_ERROR)
        {
            printf("\tFailed, RPN_Evaluate produced an error\n");
        }
        else if (fabs(temp - f_test_results[i]) > 0.0001)
        {
            printf("\tFailed, expected = %f , result = %f\n", f_test_results[i], temp);
        }
        else
        {
            printf("   Success!\n");
        }
    }
    
    //* test complex testcases
    for (int i = 0; i < 5; i++)
    {
        printf("Testing RPN_Evaluate with \"%s\"... \n ", complex_test_cases[i]);
        if (RPN_Evaluate(complex_test_cases[i], &temp) != RPN_NO_ERROR)
        {
            printf("\tFailed, RPN_Evaluate produced an error\n");
        }
        else if (fabs(temp - complex_test_results[i]) > 0.0001)
        {
            printf("\tFailed, expected = %f , result = %f\n", complex_test_results[i], temp);
        }
        else
        {
            printf("   Success!\n");
        }
    }

    //* test error testcases
    int error_temp;
    for (int i = 0; i < 14; i++)
    {
        printf("Error testing RPN_Evaluate with \"%s\"... \n ", error_test_cases[i]);
        error_temp = RPN_Evaluate(error_test_cases[i], &temp);
        if (error_temp == RPN_NO_ERROR)
        {
            printf("\tFailed, RPN_Evaluate did not produce an error\n");
        }
        else if (abs(error_temp - error_test_results[i]) > 0.0001)
        {
            printf("\tFailed, expected = %d , result = %d\n", error_test_results[i], error_temp);
        }
        else
        {
            printf("   Success!\n");
        }
    }
    
    //* test processbackspaces
    for (int i = 0; i < 8; i++)
    {
        char test_string[MAX_STR_LEN];
        strcpy(test_string, process_backspaces_test_cases[i]);

        ProcessBackspacesTestPrint(test_string); // use helper function to display /b /n

        ProcessBackspaces(test_string);
        
        if (!strcmp(test_string, process_backspaces_test_results[i]))
        {
            printf("\tSuccess!\n");
        }
        else
        {
            printf("\tFailed, result \"%s\", expected \"%s\"\n", test_string, process_backspaces_test_results[i]);
        }
    }
    
    
    BOARD_End();
    while (1);
}

void ProcessBackspacesTestPrint(char* test_string)
{
    printf("Testing ProcessBackspaces with \"");

    while (*test_string != '\0')
    {
        if (*test_string == '\n')
        {
            printf("\\n");
        }
        else if (*test_string == '\b')
        {
            printf("\\b");
        }
        else
        {
            putchar(*test_string);
        }

        test_string++;
    }

    printf("\"\n");
}



