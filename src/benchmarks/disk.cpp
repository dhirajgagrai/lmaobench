#include <chrono>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

using namespace std::chrono;

void run_disk_benchmark(const char *disk_path) {
    constexpr size_t BLOCK_SIZE  = 512;
    constexpr size_t BLOCK_COUNT = 10000;

    char buffer[BLOCK_SIZE];
    int  fd = open(disk_path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }

    auto start = high_resolution_clock::now();

    for (int i = 0; i < BLOCK_COUNT; ++i) {
        off_t   offset   = i * BLOCK_SIZE;
        ssize_t bytes_rd = pread(fd, buffer, BLOCK_SIZE, offset);
        if (bytes_rd != BLOCK_SIZE) {
            perror("pread");
            close(fd);
            return;
        }
    }

    auto end = high_resolution_clock::now();
    close(fd);

    auto   total_ns = duration_cast<nanoseconds>(end - start).count();
    double avg_ns   = static_cast<double>(total_ns) / BLOCK_COUNT;

    std::cout << "[latency][disk] read 512 bytes: " << avg_ns << " ns\n";
}
