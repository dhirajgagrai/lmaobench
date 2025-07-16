#include <cerrno>
#include <chrono>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

using namespace std::chrono;

std::string gen_file_name(int n) {
    std::string s;
    do {
        char letter = static_cast<char>('a' + (n % 26));
        s.insert(s.begin(), letter);
        n = n / 26 - 1;
    } while (n != -1);
    return s;
}

void run_fs_benchmark(int iterations = 1000) {
    const char *dir = "tests";

    if (mkdir(dir, 0755) < 0) {
        if (errno == EEXIST) {
            std::cout << "WARNING: 'tests' directory already exists.\n";
        } else {
            perror("mkdir failed");
            return;
        }
    }

    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        std::string file_name = std::string(dir) + "/" + gen_file_name(i);

        int fd = open(file_name.c_str(), O_CREAT | O_EXCL, 0644);
        if (fd < 0) {
            perror("open");
            return;
        }

        close(fd);
    }

    auto end = high_resolution_clock::now();

    auto   total_ns = duration_cast<nanoseconds>(end - start).count();
    double avg_ns   = static_cast<double>(total_ns) / iterations;

    std::cout << "[latency][fs] create: " << avg_ns << " ns\n";

    start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        std::string file_name = std::string(dir) + "/" + gen_file_name(i);
        if (unlink(file_name.c_str()) < 0) {
            perror("unlink failed");
            return;
        }
    }

    end = high_resolution_clock::now();

    total_ns = duration_cast<nanoseconds>(end - start).count();
    avg_ns   = static_cast<double>(total_ns) / iterations;

    std::cout << "[latency][fs] delete: " << avg_ns << " ns\n";

    if (rmdir(dir) < 0) {
        if (errno == ENOTEMPTY) {
            std::cout
                << "WARNING: Benchmark was unable to delete all items inside 'tests' directory. "
                   "Remove it manually.\n";
        } else {
            perror("rmdir failed");
            return;
        }
    };
}
