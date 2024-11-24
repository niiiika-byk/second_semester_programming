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

        for (int i = 0; i < size; ++i) {
            Data value;
            ifs.read(reinterpret_cast<char*>(&value), sizeof(Data));
            push(value);
        }

        ifs.close();
    }

    void display() {
        Node<Data>* current = this->head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

private:
    Node<Data>* head;
};