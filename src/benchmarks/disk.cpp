#include <chrono>
#include <fcntl.h>
#include <unistd.h>

using namespace std::chrono;

void run_disk_benchmark(int iterations = 1000000) {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
    }

    auto end = high_resolution_clock::now();
}
