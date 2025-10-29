import time


def get_time_us():
    return time.perf_counter() * 1e6


def heavy_task(N):
    sum_v = 0.0
    for i in range(N):
        sum_v += i * 0.1234
    return sum_v


def benchmark():
    N = 50 * 1000 * 1000  # 50 million ops

    # Warm-up
    for _ in range(3):
        heavy_task(N // 10)

    total_us = 0.0
    test_runs = 10

    for i in range(test_runs):
        start = get_time_us()
        _ = heavy_task(N)
        end = get_time_us()

        elapsed = end - start
        total_us += elapsed

        print(f"Run {i+1:2d}: {elapsed/1000.0:.3f} ms ({elapsed:.0f} us)")

    avg = total_us / test_runs
    print(f"\nAverage: {avg/1000.0:.3f} ms ({avg:.0f} us)")


if __name__ == "__main__":
    benchmark()
