#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <barrier>

//Barrier — примитив синхронизации, позволяет нескольким потокам синхронизироваться на опр. точке выполнения. 
//Каждый поток может достигать барьера, и он будет заблокирован, пока все потоки не достигнут этой точки. 
//Как только все потоки достигли барьера, они могут продолжить выполнение.

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

void worker(int id, std::barrier<>& barrier, int num_chars) {
    // Ожидание других потоков
    barrier.arrive_and_wait();

    auto start_time = std::chrono::high_resolution_clock::now();

    // Синхронизация вывода
    {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Thread " << id << " has entered.\n";
        
        // Генерация случайных символов
        std::string random_chars = generate_random(num_chars);
        std::cout << "Thread " << id << ": " << random_chars << std::endl;
    }

    //std::this_thread::sleep_for(std::chrono::seconds(1));

    auto end_time = std::chrono::high_resolution_clock::now(); // Конец работы
    std::chrono::duration<double> duration = end_time - start_time; // Вычисление времени

    {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Thread " << id << " is leaving. Time: " << duration.count() << " seconds.\n";
    }
}

int main() {
    const int num_threads = 5;
    const int max_threads = 2;
    const int num_chars = 10; // Количество случайных символов для генерации

    std::barrier<> barrier(num_threads); // Создаем барьер для num_threads потоков

    std::thread threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(worker, i, std::ref(barrier), num_chars);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}