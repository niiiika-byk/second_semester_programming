#include "thread.hpp"

int main() {
    int num_threads = 5; // количество потоков
    int num_chars = 10;  // количество символов

    // без примитивов
    withoud_primitives(num_threads, num_chars);

    // с mutex
    benchmark_mutex(num_threads, num_chars);

    // с semaphore
    benchmark_semaphore(num_threads, num_chars);

    return 0;
}