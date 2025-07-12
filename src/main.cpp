#include <iostream>

void run_syscall_benchmark(int iterations);
void run_signal_benchmark(int iterations);

int main(int argc, char **argv) {
    std::cout << "=== lmao bench ===\n";
    run_syscall_benchmark(1'000'000);
    run_signal_benchmark(1'000'000);
    return 0;
}
