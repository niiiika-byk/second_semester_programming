#include <atomic>
#include <thread>
#include <iostream>
#include <mutex>
#include <random>
#include <chrono>
#include <string>

//SpinLock — примитив синхронизации, основанный на атомарных операциях atomic flag. 
//Работает путем активного ожидания. Если поток не может захватить блокировку, он постоянно 
//проверяет состояние блокировки в цикле, пока не сможет ее захватить. 
//Использует вместо блокировки потока сам цикл.

class SpinLock {
public:
    SpinLock() : flag(ATOMIC_FLAG_INIT) {}

    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            //ожидание
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release); //очистка флага
    }

private:
    std::atomic_flag flag; //бинарный флаг для блокировки
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

void worker(int id, SpinLock& spinlock, int num_chars) {
    spinlock.lock();
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
    
    spinlock.unlock();
}

int main() {
    const int num_threads = 5;
    int num_chars = 10;
    
    SpinLock spinlock;
    
    std::thread threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(worker, i, std::ref(spinlock), num_chars);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}