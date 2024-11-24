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

    void serialize(const std::string& filename) {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs.is_open()) {
            throw std::runtime_error("Failed to open file for writing");
        }

        int size = 0;
        Node<Data>* current = head;
        while (current != nullptr) {
            size++;
            current = current->next;
        }

        ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

        current = head;
        while (current != nullptr) {
            ofs.write(reinterpret_cast<const char*>(&current->data), sizeof(Data));
            current = current->next;
        }

        ofs.close();
    }

    void deserialize(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs.is_open()) {
            throw std::runtime_error("Cannot open file for reading");
        }

        int size = 0;
        ifs.read(reinterpret_cast<char*>(&size), sizeof(size));

        while (head != nullptr) {
            Node<Data>* next = head->next;
            delete head;
            head = next;
        }
        tail = nullptr;

        for (int i = 0; i < size; ++i) {
            Data value;
            ifs.read(reinterpret_cast<char*>(&value), sizeof(Data));
            push(value);
        }

        ifs.close();
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
