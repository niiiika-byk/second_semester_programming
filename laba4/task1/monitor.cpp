#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include <string>
#include <mutex>
#include <condition_variable>

//Monitor — примитив синхронизации, который позволяет потокам блокировать доступ к общему ресурсу,
//объединяет mutex и условную переменную.

class Monitor {
public:
    void lock() {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, [this]() { return !is_locked; });
        is_locked = true;
    }

    void unlock() {
        {
            std::lock_guard<std::mutex> lk(mtx);
            is_locked = false;
        }
        cv.notify_one(); // Уведомляем один ожидающий поток
    }

private:
    std::mutex mtx; // Мьютекс для защиты состояния
    std::condition_variable cv; // Условная переменная для ожидания
    bool is_locked = false; // Флаг блокировки
};

std::mutex output_mutex;

std::string generate_random(int length) { // Генерация случайных символов
    std::string random_chars;
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(32, 126);

    for (int i = 0; i < length; ++i) {
        char random_char = static_cast<char>(distribution(generator));
        random_chars += random_char;
    }

    return random_chars;
}

void worker(int id, Monitor& monitor, int num_chars) {
    monitor.lock();
    auto start_time = std::chrono::high_resolution_clock::now();

    {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Thread " << id << " has acquired the lock.\n";
        
        // Генерация случайных символов
        std::string random_chars = generate_random(num_chars);
        std::cout << "Thread " << id << ": " << random_chars << std::endl;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Thread " << id << " is leaving. Time: " << duration.count() << " seconds.\n";
    }
    
    monitor.unlock();
}

int main() {
    const int num_threads = 5;
    int num_chars = 10;
    
    Monitor monitor;
    
    std::thread threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(worker, i, std::ref(monitor), num_chars);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
