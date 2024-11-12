#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <limits.h>
#include <random>
#include <chrono>

//Легковесная версия семафора, для использования в многопоточных приложениях, где требуется 
//синхронизация потоков, более эффективен по сравнению с обычным, использует меньше накладных ресурсов

class SemaphoreSlim {
public:
    // начиная со второго арг. по умолчанию
    explicit SemaphoreSlim(int initialCount = 0, int maxCount = INT_MAX) 
        : count(initialCount), maxCount(maxCount) {}
    
    //блокирование потока, пока не появится место
    void Wait() {
        std::unique_lock<std::mutex> lock(mutex); 
        condition.wait(lock, [this]() { return count > 0; }); //увеомление классу для ожидания
        --count;
    }

    //освобождение потока
    void Release(int releaseCount = 1) {
        std::unique_lock<std::mutex> lock(mutex);
        count += releaseCount;
        if (count > maxCount) {
            count = maxCount;
        }
        condition.notify_one(); //уведомление о том, что место освободилось
    }

private:
    std::mutex mutex;   //блокировка
    std::condition_variable condition; //класс ожидания потока
    int count;          //количество свободных мест
    const int maxCount; //максимальное количество мест
};

// Мьютекс для синхронизации вывода
std::mutex output_mutex;

std::string generate_random(int length) { //генерация случайных символов
    std::string random_chars;
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(32, 126);

    for (int i = 0; i < length; ++i) {
        char random_char = static_cast<char>(distribution(generator));
        random_chars += random_char;
    }

    return random_chars;
}

void worker(int id, SemaphoreSlim& semaphore, int num_chars) {
    semaphore.Wait();
    auto start_time = std::chrono::high_resolution_clock::now();

    // Синхронизация вывода
    {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Thread " << id << " has entered.\n";
        
        // Генерация случайных символов
        std::string random_chars = generate_random(num_chars);
        std::cout << "Thread " << id << ": " << random_chars << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    auto end_time = std::chrono::high_resolution_clock::now(); // Конец работы
    std::chrono::duration<double> duration = end_time - start_time; // Вычисление времени

    {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Thread " << id << " is leaving. Time: " << duration.count() << " seconds.\n";
    }

    semaphore.Release();
}

int main() {
    const int num_threads = 5;
    const int max_threads = 2;
    const int num_chars = 10; // Количество случайных символов для генерации

    SemaphoreSlim semaphore(max_threads);

    std::thread threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(worker, i, std::ref(semaphore), num_chars);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
