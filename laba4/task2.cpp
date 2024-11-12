#include "task2.hpp"
std::mutex mutex; // Глобальный мьютекс

void students_to_deduction(const std::vector<Student>& students, std::vector<std::string>& result, int Z, int K, int start, int end) {
    std::vector<std::string> local_result;
    for (int i = start; i < end; ++i) {
        if (students[i].count_debt > Z && students[i].course > K) {
            local_result.push_back(students[i].name);
        }
    }
    
    // Блокируем доступ к общему вектору result
    std::lock_guard<std::mutex> lock(mutex);
    result.insert(result.end(), local_result.begin(), local_result.end());
}

std::string generate_random_name() {
    const std::vector<std::string> names = {
        "Иванов", "Петров", "Сидоров", "Козлов", "Смирнов",
        "Кузнецов", "Васильев", "Михайлов", "Николаев", "Дмитриев",
        "Александров", "Владимиров", "Сергеев", "Андреев", "Максимов",
        "Егоров", "Алексеев", "Артемьев", "Александрова", "Еленивская"
    };
    static std::mt19937 rng(std::random_device{}()); // Генератор случайных чисел
    std::uniform_int_distribution<int> dist(0, names.size() - 1);
    return names[dist(rng)];
}

void single_thread(const std::vector<Student>& students, std::vector<std::string>& result, int Z, int K) {
    students_to_deduction(students, result, Z, K, 0, students.size());
}

void multi_thread(const std::vector<Student>& students, std::vector<std::string>& result, int Z, int K, int num_threads) {
    int size_thread = students.size() / num_threads;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * size_thread;
        int end = (i == num_threads - 1) ? students.size() : (i + 1) * size_thread;
        threads.push_back(std::thread(students_to_deduction, std::ref(students), std::ref(result), Z, K, start, end));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}