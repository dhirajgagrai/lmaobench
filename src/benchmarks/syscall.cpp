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

    char byte = 'x';

    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        if (write(fd, &byte, 1) != 1) {
            std::cerr << "Write failed at iteration " << i << "\n";
            break;
        }
    }

    auto end = high_resolution_clock::now();
    close(fd);

    auto   total_ns = duration_cast<nanoseconds>(end - start).count();
    double avg_ns   = static_cast<double>(total_ns) / iterations;

    std::cout << "[latency][syscall] write (1 byte to /dev/null): " << avg_ns << " ns\n";
}
