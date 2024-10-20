#include <string>
#include <iostream>

#include "struct_data_base.hpp"

using namespace std;

void LinkedList::push_front(const std::string& value) {
    Node* newNode = new Node(value, nullptr, this->head);
    if (this->head != nullptr) {
        newNode->next = head;
        this->head = newNode;
    }
    if (this->tail == nullptr) {
        this->tail = newNode;
        this->head = newNode;
    }
}

void LinkedList::push_back(const std::string& value) {
    Node* newNode = new Node(value, nullptr);
    if (this->tail != nullptr) {
        this->tail->next = newNode;
        this->tail = newNode;
    }
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
    }
}

void LinkedList::insert(int index, const std::string& value){
    if (index < 0) {
        std::cout << "Invalid index" << std::endl;
        return;
    }

    Node* new_node = new Node(value, nullptr);

    if (index == 0) {
        new_node->next = head;
        head = new_node;

        if (tail == nullptr) {
            tail = new_node;
        }
    } else {
        Node* current = head;
        int current_index = 0;

        while (current != nullptr && current_index < index - 1) {
            current = current->next;
            current_index++;
        }

        if (current == nullptr) {
            std::cout << "Invalid index" << std::endl;
            delete new_node;
            return;
        }

        new_node->next = current->next;
        current->next = new_node;

        if (current == tail) {
            tail = new_node;
        }
    }
}

void LinkedList::pop_head(){
    if (head == nullptr) {
        std::cout << "List is empty" << std::endl;
    }
    else {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::pop_tail(){
    if (head == nullptr) {
        std::cout << "List is empty" << std::endl;
    } if (head == tail) {
        pop_head();
    } else {
        Node* node = head;
        while (node->next != tail) node = node->next;
        node->next = nullptr;
        delete tail;
        tail = node;
    }
}

void LinkedList::pop(int index){
    if (index < 0) {
        std::cout << "Invalid index" << std::endl;
        return;
    }
    Node* current = head;
    int current_index = 0;
    if (index == 0) {
        pop_head();
        return;
    } else if (current->next == tail) {
        pop_tail();
        return;
    } else {
        while (current != nullptr && current_index < index - 1) {
            current = current->next;
            current_index++;
        }
        if (current == nullptr) {
            std::cout << "Invalid index" << std::endl;
            return;
        }
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

void LinkedList::pop_value(const std::string& value){
    if (head == nullptr) return;
    if (head->data == value) {
        pop_head();
        return;
    }
    if (tail->data == value) {
        pop_tail();
        return;
    }
    Node* current = head;
    while (current != nullptr && current->data != value) {
        current = current->next;
    }
    if (current == nullptr) { // Если дошли до конца и не нашли
        std::cout << "Invalid index" << std::endl;
        return;
    }
    Node* temp = current;
    current = current->next;
    delete temp;
}

Node* LinkedList::search_value(std::string value){
    Node* current = head;
    while (current->next && current->data != value) {
        current = current->next;
    }
    if (current->data == value){
        return current;
    } else {
        cout << "Такого элемента " << current->data << " нет в списке" << endl;
        return nullptr;
    }
}

void LinkedList::display(){
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void LinkedList::clear(){
    while(head){
        pop_head();
    }
}