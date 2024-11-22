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

    bool isEmpty() {
        return head == nullptr;
    }
    Data top() {
        if (head == nullptr) {
            std::cout << "Stack is empty!" << std::endl;
            return 0;
        }
        return head->data;
    }

private:
    Node<Data>* head;
};