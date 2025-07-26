#include <cstring>
#include <iostream>

void run_syscall_benchmark(int iterations);
void run_signal_benchmark(int iterations);
void run_fs_benchmark(int iterations);
void run_disk_benchmark(const char *disk_path);

int main(int argc, char **argv) {
    const char *disk_path = nullptr;

    std::cout << "=== lmaobench ===\n";
    run_syscall_benchmark(1'000'000);
    run_signal_benchmark(1'000'000);
    run_fs_benchmark(1000);

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-disk") == 0) {
            disk_path = argv[i + 1];
            if (!disk_path) {
                std::cerr << "Usage: " << argv[0] << " -disk /dev/rdiskX\n";
                return 1;
            }

            run_disk_benchmark(disk_path);
        }
    }

    return 0;
}
