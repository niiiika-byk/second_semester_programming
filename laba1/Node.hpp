#pragma once

#include <string>

template <typename Data>
class Node {
    public:
        Data data; //поля объекта
        Node* next;
        Node* prev;

        Node(const Data& value, Node* nextNode = nullptr, Node* prevNode = nullptr) //аргументы, = дефолтный аргументы
            : data(value), next(nextNode), prev(prevNode) {
        }
};