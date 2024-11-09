#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <mutex>
#include <semaphore>

// без примитивов
void withoud_primitives(int num_threads, int num_chars);

// с mutex
void benchmark_mutex(int num_threads, int num_chars);

// с semaphore
void benchmark_semaphore(int num_threads, int num_chars);