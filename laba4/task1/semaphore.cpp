#include "thread.hpp"

std::counting_semaphore<1> semaphore(1); // Бинарный семафор (позволяет только одному потоку входить)

void generate_random_semaphore(int thread_id, int num_chars) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count() + thread_id);
    std::uniform_int_distribution<int> distribution(32, 126);

    std::string random_chars;
    for (int i = 0; i < num_chars; ++i) {
        char random_char = static_cast<char>(distribution(generator));
        random_chars += random_char;
    }

    // Используем семафор для синхронизации вывода
    semaphore.acquire(); // Захватываем семафор
    std::cout << "Thread " << thread_id << ": " << random_chars << std::endl;
    semaphore.release(); // Освобождаем семафор
}

void benchmark_semaphore(int num_threads, int num_chars) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(generate_random_semaphore, i, num_chars);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Semaphore duration: " << duration.count() << " seconds" << std::endl;
}