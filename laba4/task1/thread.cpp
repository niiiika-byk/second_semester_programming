#include "thread.hpp"

void generate_random(int thread_id, int num_chars) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count() + thread_id);
    std::uniform_int_distribution<int> distribution(32, 126);

    std::string chars;
    for (int i = 0; i < num_chars; ++i) {
        char random_char = static_cast<char>(distribution(generator));
        chars += random_char;
    }

    std::cout << "Thread " << thread_id << ": " << chars << std::endl;
}

void withoud_primitives(int num_threads, int num_chars) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(std::thread(generate_random, i, num_chars));
    }

    for (auto& thread : threads) {
        thread.join();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Without primitives: " << duration.count() << " seconds\n" << std::endl;
}