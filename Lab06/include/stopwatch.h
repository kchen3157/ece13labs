/**
 * stopwatch.h
 *
 * NOTE: Uses C11.
 * NOTE: Timing resolution can be enhanced on POSIX-compatible systems with
 *       clock_gettime().
 *
 * @author  HARE Lab
 * @author  jLab
 * @version 1.0.0
 *
 * @date    25 Mar 2025
 */
#ifndef STOPWATCH_H
#define STOPWATCH_H

#ifdef STM32F4
#include <BOARD.h>
#include <Timers.h>
#else
#include <time.h>
#endif /*  STM32F4 */

// Macro declarations for STM32F4 compatibility.
#ifdef STM32F4
#define CLOCKS_PER_SEC Timers_GetSystemClockFreq()
#define clock() Timers_GetMicroSeconds()
#endif /*  STM32F4 */

// Function prototypes.
/**Stopwatch_Init()
 *
 * Configure system for clock usage.
 *
 * @returns success (int) : 0 for success, 1 for failure.
 */
int Stopwatch_Init(void);
/**Stopwatch_StartBenchmark()
 *
 * Initializes benchmark CPU cycle count and time for benchmark.
 *
 * @returns success (int) : 0 for success, 1 for failure.
 */
int Stopwatch_StartBenchmark(void);
/**Stopwatch_StopBenchmark()
 *
 * Gets benchmark CPU cycle count and time for benchmark and prints to STDOUT.
 *
 * @returns success (int) : 0 for success, 1 for failure.
 */
int Stopwatch_StopBenchmark(void);

/**Stopwatch_PrintBenchmarkResults()
 *
 * Output results of the benchmark to STDOUT.
 */
void Stopwatch_PrintBenchmarkResults(void);

#endif /*  STOPWATCH_H */
