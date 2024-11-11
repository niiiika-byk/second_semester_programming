#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector> 

class Philosopher {
public:
    Philosopher(int id, std::mutex& _first_fork, std::mutex& _second_fork)
        : id(id), left_fork(_first_fork), right_fork(_second_fork), meals_eaten(0) {}

    void action() {
        while (meals_eaten < 3) { //философ будет есть 3 раза

            //думаем
            {
                std::lock_guard<std::mutex> lock(output_mutex);
                std::cout << "Философ " << id << " думает." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 1000)); //думаем 1- 2 c.

            //захват вилок
            std::lock(left_fork, right_fork); //фиксируем обе
            std::lock_guard<std::mutex> lg1(left_fork, std::adopt_lock); //левая
            std::lock_guard<std::mutex> lg2(right_fork, std::adopt_lock); //правая

            //едим
            {
                std::lock_guard<std::mutex> lock(output_mutex);
                std::cout << "Философ " << id << " начал есть." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 500)); //кушаем 1- 2 c.
            meals_eaten++; //счетчик приемов

            // Мыслитель освобождает вилки
            {
                std::lock_guard<std::mutex> lock(output_mutex);
                std::cout << "Философ " << id << " освободил вилки." << std::endl; //снятие фиксации
            }
        }

        //завершение обеда
        {
            std::lock_guard<std::mutex> lock(output_mutex);
            std::cout << "\tФилософ " << id << " поел после " << meals_eaten << " раз." << std::endl;
        }
    }
    
private:
    int id;
    std::mutex& left_fork;
    std::mutex& right_fork;
    int meals_eaten;
    static std::mutex output_mutex;
};

std::mutex Philosopher::output_mutex; //мьютекс для вывода

int main() {
    const int num_threads = 5;
    std::vector<std::thread> philosophers_threads; //вектор для потоков
    std::vector<std::mutex> forks(num_threads); //мьютексы для вилок

    // Создаем философов
    for (int i = 0; i < num_threads; ++i) {
        std::mutex& left_fork = forks[std::min(i, (i + 1) % num_threads)];
        std::mutex& right_fork = forks[std::max(i, (i + 1) % num_threads)];
        philosophers_threads.emplace_back(&Philosopher::action, Philosopher(i, left_fork, right_fork));
    }

    // Запуск потоков
    for (auto& thread : philosophers_threads) {
        thread.join();
    }

    return 0;
}