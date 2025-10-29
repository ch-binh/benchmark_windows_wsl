#include <stdio.h>
#include <stdint.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

double get_time_us()
{
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart * 1e6 / (double)freq.QuadPart;
}

#else
#include <time.h>

double get_time_us()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1e6 + (double)ts.tv_nsec / 1e3;
}

#endif

// Example workload: simple math loop
static inline double heavy_task(int N)
{
    double sum = 0.0;
    for (int i = 0; i < N; i++)
    {
        sum += i * 0.1234;
    }
    return sum;
}

int main()
{
    const int N = 50 * 1000 * 1000; // 50 million ops
    double start = get_time_us();

    double result = heavy_task(N);

    double end = get_time_us();
    double elapsed_us = end - start;

    printf("Task result: %.2f\n", result);
    printf("Elapsed: %.3f ms (%.0f us)\n", elapsed_us / 1000.0, elapsed_us);

    return 0;
}
