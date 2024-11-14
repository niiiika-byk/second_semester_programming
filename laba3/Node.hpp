#pragma once

#include <string>

template <typename Data>
class LinkedList;
template <typename Data>
class DoublyList;
template <typename Data>
class Queue;
template <typename Data>
class Stack;

template <typename Data>
class Node {
public:
    Node(const Data& value, Node* nextNode = nullptr, Node* prevNode = nullptr) //аргументы, = дефолтный аргументы
        : data(value), next(nextNode), prev(prevNode) {
    }

    friend class LinkedList<Data>;
    friend class DoublyList<Data>;
    friend class Queue<Data>;
    friend class Stack<Data>;

private:
    Data data; //поля объекта
    Node* next;
    Node* prev;
};