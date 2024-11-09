#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>

class Student {
public:
    std::string name;
    int course;
    int count_debt;

    Student(std::string _name, int _course, int _count_debt): name(_name), course(_course), count_debt(_count_debt) {}

    ~Student() = default;
};

void students_to_deduction(const std::vector<Student>& students, std::vector<std::string>& result, int Z, int K, int start, int end);
void single_thread(const std::vector<Student>& students, std::vector<std::string>& result, int Z, int K);
void multi_thread(const std::vector<Student>& students, std::vector<std::string>& result, int Z, int K, int num_threads);