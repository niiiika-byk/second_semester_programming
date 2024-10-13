#pragma once
#include <iostream>
#include <fstream>

template <typename Data>
class Array {
public:
    Data* array;
    int size;       // размерность массива
    int capacity; // текущая ёмкость массива

    Array() : array(nullptr), size(0), capacity(10) {
        array = new Data[capacity];
    }

    ~Array() {
        delete[] array;
    }

    void push_back(const Data& value){
        if (size == capacity) {
            int newCapacity = capacity * 2;
            Data* newArray = new Data[newCapacity];

            for (int i = 0; i < size; i++) {
                newArray[i] = array[i];
            }

            delete[] array;
            array = newArray;
            capacity = newCapacity;
        }

        array[size] = value;
        size++;
    }

    void display(){
        if (size == 0) {
            std::cout << "Array is empty." << std::endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    void find_sum (int targetSum) {
        for (int start = 0; start < size; start++) {
            int currentSum = 0; // текущая сумма подмассива
            for (int end = start; end < size; end++) {
                currentSum += array[end]; // добавляем текущий элемент
                if (currentSum == targetSum) {
                    std::cout << "Subarray found: [";
                    for (int i = start; i <= end; i++) {
                        std::cout << array[i];
                        if (i < end) std::cout << ", ";
                    }
                    std::cout << "]" << std::endl;
                }
            }
        }
    }
};