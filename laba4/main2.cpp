#include "task2.hpp"

int main() {
    int debt = 2;
    int number_course = 2;
    int num_threads = 4;

    std::vector<Student> students = {
        {"Иванов", 3, 1},
        {"Петров", 4, 3}, //отчислен
        {"Сидоров", 2, 0},
        {"Козлов", 5, 4}, //отчислен
        {"Смирнов", 3, 2},
        {"Кузнецов", 4, 5}, //отчислен
        {"Васильев", 2, 1},
        {"Михайлов", 3, 3}, //отчислен
        {"Николаев", 4, 2},
        {"Дмитриев", 5, 6}, //отчислен
        {"Александров", 2, 0},
        {"Владимиров", 3, 2},
        {"Сергеев", 4, 1},
        {"Андреев", 5, 3} //отчислен
    };

    std::vector<std::string> result_single;
    std::vector<std::string> result_multi;

    auto start_time = std::chrono::high_resolution_clock::now();
    single_thread(students, result_single, debt, number_course);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time_single = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    start_time = std::chrono::high_resolution_clock::now();
    multi_thread(students, result_multi, debt, number_course, num_threads);
    end_time = std::chrono::high_resolution_clock::now();
    auto time_multi = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "Время однопоточной обработки: " << time_single << " микросекунд\n";
    std::cout << "Время многопоточной обработки: " << time_multi << " микросекунд\n";

    std::cout << "Студенты на отчисление (однопоточная обработка):\n";
    for (const auto& name : result_single) {
        std::cout << "\t" << name << "\n";
    }

    std::cout << "Студенты на отчисление (многопоточная обработка):\n";
    for (const auto& name : result_multi) {
        std::cout << "\t" << name << "\n";
    }

    return 0;
}