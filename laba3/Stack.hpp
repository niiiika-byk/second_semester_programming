#include <iostream>
#include <fstream>

#include "Node.hpp"

template <typename Data>
class Stack {
public:
    Stack() : head(nullptr) {}
    void push(const Data& value) {
        Node<Data>* newNode = new Node<Data>(value, this->head);
        this->head = newNode;
    }
    void pop() {
        if (this->head == nullptr) {
            std::cout << "Stack is empty!" << std::endl;
            return;
        }
        Node<Data>* next = this->head->next;
        delete this->head;
        this->head = next;
    }
    void search(const Data& value) {
        Node<Data>* current = this->head;
        while (current != nullptr) {
            if (current->data == value) {
                std::cout << "Found!" << std::endl;
                return;
            }
            current = current->next;
        }
        std::cout << "Not found!" << std::endl;
    }
    void display() {
        Node<Data>* current = this->head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void load_from_file(std::string filename) {
        while (head) { // очищаем текущий лист
            pop();
        }
        head = nullptr; // Обновляем указатели

        std::ifstream file(filename);
        if (!file) {
            std::cout << "File not found" << std::endl;
            return;
        }

        std::string line;
        while (getline(file, line)) {
            push(line); // добавляем в конец массива
        }
        file.close();
    }
    bool isEmpty() {
        return head == nullptr;
    }
    Data top() {
        if (head == nullptr) {
            std::cout << "Stack is empty!" << std::endl;
        }
        return head->data;
    }
    void save_to_file(std::string filename) {
        std::ofstream file(filename);
        if (!file) {
            std::cout << "File not found" << std::endl;
            return;
        }

        Node<Data>* current = head;
        Stack<Data> tempStack;

        while (current != nullptr) {
            tempStack.push(current->data);
            current = current->next;
        }

        while (!tempStack.isEmpty()) {
            file << tempStack.top() << std::endl;
            tempStack.pop();
        }

        file.close();
    }

private:
    Node<Data>* head;
};