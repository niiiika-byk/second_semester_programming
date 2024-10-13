#include <iostream>
#include <fstream>

#include "Node.hpp"

template <typename Data>
class Stack {
public:
    Node<Data>* head;

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
    Data top() {
        if (this->head == nullptr) {
            throw std::runtime_error("Stack is empty!");
        }
        return this->head->data;
    }

    bool isEmpty() {
        return this->head == nullptr;
    }
};