#include <iostream>

void run_syscall_benchmark(int iterations);
void run_signal_benchmark(int iterations);
void run_fs_benchmark(int iterations);

int main(int argc, char **argv) {
    std::cout << "=== lmaobench ===\n";
    run_syscall_benchmark(1'000'000);
    run_signal_benchmark(1'000'000);
    run_fs_benchmark(1000);
    return 0;
}
