#include <iostream>
#include <fstream>

template <typename Data>
class Array {
public:
    Array() : array(nullptr), size(0), capacity(2) {
        array = new Data[capacity];
    }

    ~Array() {
        delete[] array;
    }

    void push_front(const Data& value){ //добавление в начало массива
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
        for (int i = size; i > 0; i--) { 
            array[i] = array[i - 1];
        }

        array[0] = value;
        size++;
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

    void push_in(int index, const Data& value){
        if (index < 0 || index > size) {
            std::cout << "Invalid index" << std::endl;
            return;
        }

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

        for (int i = size; i > index; i--) {
            array[i] = array[i - 1];
        }

        array[index] = value;
        size++;
    }

    void pop_front(){
        if (size <= 0) {
            std::cout << "Array is empty, cannot pop front." << std::endl;
        } else {
            for (int i = 0; i < size - 1; i++) {
                array[i] = array[i + 1];
            }
            size--;
        }
    }

    void pop_back(){
        if (size > 0) {
            size--;
        } else {
            std::cout << "Array is empty, cannot pop back." << std::endl;
        }
    }

    void pop_in(int index){
        if (index < 0 || index >= size) {
            std::cout << "Invalid index" << std::endl;
            return;
        }
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        size--;
    }

    bool search(const Data& value){
        for (int i = 0; i < size; i++) {
            if (array[i] == value) {
                std::cout << "Found!" << std::endl;
                return true;
            }
        }
        std::cout << "Not found!" << std::endl;
        return false;
    }

    bool search_index(const int index){
        if (index >= 0 && index < size) {
            std::cout << array[index] << std::endl;
            return true;
        } else {
            std::cout << "Invalid index" << std::endl;
            return false;
        }
    }

    void set_value_at(int index, int value) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index" << std::endl;
            return;
        }

        array[index] = value;
    }

    Data get_value_at(int index) {
        if (index >= 0 && index < size) {
            return array[index];
        } else {
            std::cout << "Invalid index" << std::endl;
            throw std::out_of_range("Index out of range");
        }
    }

    int get_size(){
        return size;
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

private:
    Data* array;
    int size;       // размерность массива
    int capacity; // текущая ёмкость массива
};