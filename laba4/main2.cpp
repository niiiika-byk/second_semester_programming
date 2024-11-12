#include "task2.hpp"

int main() {
    int num_students;
    int debt;
    int number_course;
    int num_threads = 4;

    // Ввод данных с консоли
    std::cout << "Введите количество студентов: ";
    std::cin >> num_students;
    std::cout << "Введите курс, который проверяем: ";
    std::cin >> number_course;
    std::cout << "Введите количество задолженностей: ";
    std::cin >> debt;

    std::vector<Student> students;

    // Заполнение вектора случайными данными
    for (int i = 0; i < num_students; ++i) {
        students.push_back({generate_random_name(), rand() % 6 + 1, rand() % 6}); // Курс от 1 до 5, задолженности от 0 до 5
    }

    std::vector<std::string> result_single;
    std::vector<std::string> result_multi;

    auto start_time = std::chrono::high_resolution_clock::now();
    single_thread(students, result_single, debt, number_course);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time_single = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Время однопоточной обработки: " << time_single / 1'000'000.0 << " секунд\n";

    start_time = std::chrono::high_resolution_clock::now();
    multi_thread(students, result_multi, debt, number_course, num_threads);
    end_time = std::chrono::high_resolution_clock::now();
    auto time_multi = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Время многопоточной обработки: " << time_multi / 1'000'000.0 << " секунд\n";

    // std::cout << "Студенты на отчисление (однопоточная обработка):\n";
    // for (const auto& name : result_single) {
    //     std::cout << " " << name << " ";
    // }
    // std::cout << "\n";

    // std::cout << "Студенты на отчисление (многопоточная обработка):\n";
    // for (const auto& name : result_multi) {
    //     std::cout << " " << name << " ";
    // }
    // std::cout << "\n";

    return 0;
}