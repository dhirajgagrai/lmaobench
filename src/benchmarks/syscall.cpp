#include <chrono>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

using namespace std::chrono;

void run_syscall_benchmark(int iterations = 1000000) {
    int fd = open("/dev/null", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open /dev/null");
        return;
    }

    uint64_t word = 0xFFFFFFFFFFFFFFFF;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        if (write(fd, &word, 1) != 1) {
            std::cerr << "Write failed at iteration " << i << "\n";
            break;
        }
    }

    auto end = high_resolution_clock::now();
    close(fd);

    auto   total_ns = duration_cast<nanoseconds>(end - start).count();
    double avg_ns   = static_cast<double>(total_ns) / iterations;

    std::cout << "[latency][syscall] entry (write 1 word to /dev/null): " << avg_ns << " ns\n";
}
