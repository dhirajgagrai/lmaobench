#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <unistd.h>

using namespace std::chrono;

std::atomic<bool> signal_recieved{false};

void signal_handler(int signum) {
    signal_recieved.store(true, std::memory_order_relaxed);
}

void run_signal_benchmark(int iterations = 1000000) {
    struct sigaction act{};
    act.sa_handler = &signal_handler;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        if (sigaction(SIGUSR1, &act, NULL) < 0) {
            perror("Failure in signal installation");
            return;
        }
    }

    auto end = high_resolution_clock::now();

    auto   total_ns = duration_cast<nanoseconds>(end - start).count();
    double avg_ns   = static_cast<double>(total_ns) / iterations;

    std::cout << "[latency][signal] sigaction: " << avg_ns << " ns\n";

    start = high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        signal_recieved.store(false, std::memory_order_relaxed);
        if (kill(getpid(), SIGUSR1) < 0) {
            perror("Failure in sending signal");
        }
        while (!signal_recieved.load(std::memory_order_relaxed))
            ;
    }

    end = high_resolution_clock::now();

    total_ns = duration_cast<nanoseconds>(end - start).count();
    avg_ns   = static_cast<double>(total_ns) / iterations;

    std::cout << "[latency][signal] sig handler: " << avg_ns << " ns\n";
}
