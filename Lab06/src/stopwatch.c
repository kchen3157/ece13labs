/**
 * @file    stopwatch.c
 *
 * A benchmarking tool that measures time in terms of clock cycles and ms.
 *
 * This tool runs on both x86_64 and STM32F4 embedded systems. It does not
 * (currently) return any information about the clock used, instead simply
 * reporting on information to STDOUT.
 *
 * @usage
 *    1. Stopwatch_Init()           <-- Configures system clock; only needs to
 *                                      be called once.
 *    2. Stopwatch_StartBenchmark() <-- Starts the timer counting; will restart
 *                                      count if called multiple times without
 *                                      error.
 *    3. Stopwatch_StopBenchmark()  <-- Stops the clock; this will set the
 *                                      benchmark cycles/time relative to the
 *                                      last invocation of
 *                                      "Stopwatch_StartBenchmark()".
 *    4. Stopwatch_PrintBenchmarkResults()  <-- Outputs info about cycles/time
 *                                              of benchmark.
 *
 * @author  HARE Lab
 * @author  jLab
 * @version 1.0.0
 *
 * @date    September 17, 2024
 */
#include <stdio.h>
#include <stdlib.h>

#include "stopwatch.h"

// Module-level variables.
static clock_t start_cycle;
static clock_t end_cycle;

// Library.
/**Stopwatch_Init()
 *
 * Configure system for clock usage.
 *
 * @returns success (int) : 0 for success, 1 for failure.
 */
int Stopwatch_Init(void)
{
  int success = 0;
#ifdef STM32F4
  success = Timers_Init() ? 0 : 1;
#endif /*  STM32F4 */
  return success;
}

/**Stopwatch_StartBenchmark()
 *
 * Initializes benchmark CPU cycle count and time for benchmark.
 *
 * @returns success (int) : 0 for success, 1 for failure.
 */
int Stopwatch_StartBenchmark(void)
{
  start_cycle = clock();
  if (!start_cycle)
  {
    return 1;
  }
  return 0;
}

int Stopwatch_StopBenchmark(void)
{
  /**Stopwatch_StopBenchmark()
   *
   * Gets benchmark CPU cycle count and time for benchmark and prints to STDOUT.
   *
   * @returns success (int) : 0 for success, 1 for failure.
   */
  end_cycle = clock();
  if (!end_cycle)
  {
    return 0;
  }
  return 1;
}

void Stopwatch_PrintBenchmarkResults(void)
{
  /**Stopwatch_PrintBenchmarkResults()
   *
   * Output results of the benchmark to STDOUT.
   */
  if (!start_cycle || !end_cycle)
  {
    printf("ERROR: Please run benchmark before printing results!\r\n");
    return;
  }
#ifdef STM32F4
  uint32_t duration_cycles = end_cycle - start_cycle;
  float duration_ms = (float)duration_cycles / (1000.0); // us to ms
#else
  unsigned long duration_cycles = end_cycle - start_cycle;
  float duration_ms = (float)duration_cycles / (float)CLOCKS_PER_SEC;
#endif /*  STM32F4 */
  printf(
      "Program took %lu cycles and %f ms to complete.\r\n",
      duration_cycles,
      duration_ms);
}
