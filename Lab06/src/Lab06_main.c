/**
 * @file  Lab06_main.c
 *
 * Benchmarking script for different sorting methods.
 *
 * @date    27 Oct 2024
 */
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>

// Course support library.
#include <BOARD.h>

// User libraries.
#include "LinkedList.h"
#include "sort.h"
#include "stopwatch.h"

// Define a somewhat-robust SLEEP.
#ifdef STM32F4 // Nucleo
#define SLEEP(ms) HAL_Delay(ms)
#elif _WIN32 // Windows
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#elif __unix || __APPLE__ // Linux, MacOS, other UNIX-like systems
#include <unistd.h>
#define SLEEP(ms)          \
    do                     \
    {                      \
        usleep(ms * 1000); \
    } while (0)
#else // Unknown system.
#error "Unknown system"
#endif /*  All OSes. */

/**
 * _checkHeapStatus(ListItem* listToSort)
 *
 * Handler for heap overflow errors. If a NULL pointer is found on an embedded
 * system, enter a "safe" state by spinning in a while() loop forever. If the
 * NULL pointer is encountered in the development environment, exit with code 2.
 * If no NULL pointer is found, simply continue.
 *
 * @param ListItem* listToSort  - Pointer to check for error.
 */
static void _checkHeapStatus(ListItem *listToSort)
{
    if (!listToSort)
    {
        printf(
            "\r\n FATAL ERROR: Maximum heap size exceeded! "
            "Please reboot this system to proceed.\r\n");
#ifdef STM32F4
        while (1 < 2)
            ;
#else
        exit(2);
#endif /*  STM32F4 */
    }
}

int main(void)
{
    BOARD_Init();
    Stopwatch_Init();

#ifdef STM32F4
    // Wait for the serial monitor to connect...
    SLEEP(3000);
#endif /*  STM32F4 */

    printf(
        "\r\n\r\nWelcome to CRUZID's Lab06_main.c, "
        "compiled on %s %s.\r\n",
        __DATE__, __TIME__);

    ListItem *listToSort;

    // First, benchmark SelectionSort():
    printf("\r\nStarting stopwatch for SelectionSort()...\r\n");
    listToSort = CreateUnsortedList();
    _checkHeapStatus(listToSort);

    Stopwatch_StartBenchmark();
    listToSort = SelectionSort(listToSort);
    Stopwatch_StopBenchmark();
    LinkedListPrint(listToSort);
    Stopwatch_PrintBenchmarkResults();

    SLEEP(5);

    // Next, benchmark InsertionSort():
    printf("\r\nStarting stopwatch for InsertionSort()...\r\n");
    listToSort = CreateUnsortedList();
    _checkHeapStatus(listToSort);

    Stopwatch_StartBenchmark();
    listToSort = InsertionSort(listToSort);
    Stopwatch_StopBenchmark();
    LinkedListPrint(listToSort);
    Stopwatch_PrintBenchmarkResults();

    BOARD_End();
#ifdef STM32F4
    while (1)
        ;
#endif /*  STM32F4 */
}
