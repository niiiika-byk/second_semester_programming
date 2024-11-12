#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include <chrono>
#include <string>
#include <atomic>

//SpinWait — примитив синхронизации, который используется в многопоточных приложениях 
//для активного ожидания (или "кручения") в цикле, пока не будет выполнено определенное условие.
//Позволяет потоку ожидать в цикле, вместо блокировки.

class SpinWait {
public:
    SpinWait() : flag(false) {}

    void lock() {
        while (flag.exchange(true, std::memory_order_acquire)) {
            // Активное ожидание с уступкой управления другим потокам
            std::this_thread::yield();
        }
    }

    void unlock() {
        flag.store(false, std::memory_order_release);
    }

private:
    std::atomic<bool> flag; // Флаг для блокировки
};

std::mutex output_mutex;

std::string generate_random(int length) {
    std::string random_chars;
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(32, 126);

    for (int i = 0; i < length; ++i) {
        char random_char = static_cast<char>(distribution(generator));
        random_chars += random_char;
    }

    return random_chars;
}

void worker(int id, SpinWait& spinwait, int num_chars) {
    spinwait.lock();
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
    
    spinwait.unlock();
}

int main() {
    const int num_threads = 5;
    int num_chars = 10;
    
    SpinWait spinwait;
    
    std::thread threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(worker, i, std::ref(spinwait), num_chars);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}