#include <iostream>
#include <fstream>

#include "Node.hpp"

template <typename Data>
class Queue {
public:
    Queue() : head(nullptr), tail(nullptr) {}

    ~Queue() {
        while (this->head != nullptr) {
            Node<Data>* next = this->head->next;
            delete this->head;
            this->head = next;
        }
    }

    void push (const Data& value) {
        Node<Data>* newNode = new Node<Data>(value, nullptr, this->tail);
        if (this->tail != nullptr) {
            this->tail->next = newNode;
        }
        this->tail = newNode;
        if (this->head == nullptr) {
            this->head = newNode;
        }
    }

    void search (Data value) {
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

    void pop () {
        if (this->head == nullptr) {
            std::cout << "Queue is empty!" << std::endl;
            return;
        }
        Node<Data>* next = this->head->next;
        delete this->head;
        this->head = next;
        if (this->head == nullptr) {
            this->tail = nullptr;
        }
    }

    void display () {
        if (this->head == nullptr) {
            std::cout << "Queue is empty!" << std::endl;
            return;
        }
        Node<Data>* current = this->head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

private:
    Node<Data>* head;
    Node<Data>* tail;
};
