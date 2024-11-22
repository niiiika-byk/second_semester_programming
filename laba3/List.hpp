#include <iostream>
#include <fstream>

#include "Node.hpp"

template <typename Data>
class LinkedList{
public:
    LinkedList() : head(nullptr), tail(nullptr) {};
    ~LinkedList() {
        while (this->head != nullptr) {
            Node<Data>* next = this->head->next;
            delete this->head;
            this->head = next;
        }
    }
    void push_front(const Data& value) {
        Node<Data>* newNode = new Node<Data>(value, nullptr, this->head);
        if (this->head != nullptr) {
            newNode->next = head;
            this->head = newNode;
        }
        if (this->tail == nullptr) {
            this->tail = newNode;
            this->head = newNode;
        }
    }
    void push_back(const Data& value) {
        Node<Data>* newNode = new Node<Data>(value, nullptr);
        if (this->tail != nullptr) {
            this->tail->next = newNode;
            this->tail = newNode;
        }
        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        }
    }
    void insert(int index, const Data& value){
        if (index < 0) {
            std::cout << "Invalid index" << std::endl;
            return;
        }

        Node<Data>* new_node = new Node<Data>(value, nullptr);

        if (index == 0) {
            new_node->next = head;
            head = new_node;

            if (tail == nullptr) {
                tail = new_node;
            }
        } else {
            Node<Data>* current = head;
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
    void pop_head(){
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
        }
        else {
            Node<Data>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void pop_tail(){
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
        } if (head == tail) {
            pop_head();
        } else {
            Node<Data>* node = head;
            while (node->next != tail) node = node->next;
            node->next = nullptr;
            delete tail;
            tail = node;
        }
    }
    void pop(int index){
        if (index < 0) {
            std::cout << "Invalid index" << std::endl;
            return;
        }
        Node<Data>* current = head;
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
            Node<Data>* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }
    void pop_value(Data value){
        if (head == nullptr){
            std::cout << ("List is empty") << std::endl;
            return;
        }
        if (head->data == value) {
            pop_head();
            return;
        }
        if (tail->data == value) {
            pop_tail();
            return;
        }
        Node<Data>* current = head;
        Node<Data>* previous = nullptr;

        while (current != nullptr && current->data != value) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) { // Если дошли до конца и не нашли
            std::cout << "Invalid index" << std::endl;
            return;
        }

        previous->next = current->next; // Обновляем указатель предыдущего узла
        delete current; // Удаляем узел
    }

    Data get_value(int index) const {
        if (index < 0) {
            throw std::out_of_range("Invalid index");
        }

        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }

        Node<Data>* current = head;
        int current_index = 0;

        while (current != nullptr) {
            if (current_index == index) {
                return current->data;
            }
            current = current->next;
            current_index++;
        }

        throw std::out_of_range("Invalid index");
    }
    void search(Data value){
        Node<Data>* curr = head;
        if(curr == nullptr) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        while (curr->data != value && curr->next != nullptr) {
            curr = curr->next;
        }
        if (curr->data == value)
            std::cout << "yes!" << std::endl;
        else std::cout << "No element in list" << std::endl;
    }
    void display(){
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        Node<Data>* current = head;
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


template <typename Data>
class DoublyList {
public:
    DoublyList() : head(nullptr), tail(nullptr) {};
    ~DoublyList() {
        while (this->head != nullptr) {
            Node<Data>* next = this->head->next;
            delete this->head;
            this->head = next;
        }
    }
    void push_back(const Data& value){
        Node<Data>* newNode = new Node<Data>(value, nullptr, nullptr);
        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            newNode->prev = tail;
            this->tail->next = newNode;
            this->tail = newNode;
        }
    };
    void push_front(const Data& value){
        Node<Data>* newNode = new Node<Data>(value, nullptr, nullptr);
        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            newNode->next = head;
            this->head->prev = newNode;
            this->head = newNode;
        }
    };
    void push_in(int index, const Data& value){
        Node<Data>* newNode = new Node<Data>(value, nullptr, nullptr);
        if (index < 0) {
            std::cout << "Invalid index" << std::endl;
            return;
        } if (index == 0) {
            // Вставляем в начало списка
            push_front(value);
        } else {
            Node<Data>* curr = head;
            int currentIndex = 0;

            // Находим узел, предшествующий месту вставки
            while (curr != nullptr && currentIndex < index - 1) {
                curr = curr->next;
                currentIndex++;
            }

            if (curr != nullptr) {
                // Вставляем узел после curr
                newNode->prev = curr;
                newNode->next = curr->next;
                if (curr->next != nullptr) {
                    curr->next->prev = newNode;
                } else {
                    tail = newNode;// Если вставляем в конец списка
                }
                curr->next = newNode;
            } else {
                // Индекс находится за пределами списка
                std::cout << "Index out of bounds" << std::endl;
                delete newNode;
            }
        }
    };
    void search(Data value){
        Node<Data>* curr = head;
        while (curr->data != value && curr->next != nullptr) {
            curr = curr->next;
        }
        if (curr->data == value)
            std::cout << "Yes!!" << std::endl;
        else std::cout << "No element" << std::endl;

    };
    void pop_forward(){
        if (head == nullptr) return;
        Node<Data>* curr = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr; // обновляем tail, если список стал пустым
        } else {
            head->prev = nullptr; // обновляем prev для нового head
        }
        delete curr;
    };
    void pop_backward(){
        if (tail == nullptr) return;
        Node<Data>* curr = tail;
        tail = tail->prev;
        if (tail == nullptr) {
            head = nullptr; // обновляем head, если список стал пустым
        } else {
            tail->next = nullptr; // обновляем next для нового tail
        }
        delete curr;
    };
    void pop(int index){
        if (index < 0) {
            std::cout << "Invalid index" << std::endl;
            return;
        }
        if (index == 0) { //удаление первого(индекс 0)
            pop_forward();
        }
        else {
            Node<Data>* curr = head;
            int currIndex = 0;

            while (curr != nullptr && currIndex < index) {
                curr = curr->next;
                currIndex++;
            }
            if (curr == nullptr) {//дошли до конца и не нашли нужный
                std::cout << "Invalid index" << std::endl;
                return;
            }
            if (curr->next == nullptr) {//удаляем последний 
                pop_backward();
                return;
            }
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            delete curr;
        }
    };
    void pop_value(Data value){
        if (head == nullptr) return;
        if (head->data == value) {
            pop_forward();
            return;
        }
        if (tail->data == value) {
            pop_backward();
            return;
        }
        Node<Data>* current = head;
        while (current != nullptr && current->data != value) {
            current = current->next;
        }
        if (current == nullptr) {
            std::cout << "Invalid index" << std::endl;
            return;
        }
        current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
    };
    void display(){
        Node<Data>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void load_from_file(std::string filename) {
        while (head) { // очищаем текущий лист
            pop_backward();
        }

        std::ifstream file(filename);
        if (!file) {
            std::cout << "File not found" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            push_back(line);
        }
        file.close();
    }

    void save_to_file(std::string filename) {
        std::ofstream file(filename);
        if (!file) {
            std::cout << "File not found" << std::endl;
            return;
        }

        Node<Data>* current = head;
        while (current != nullptr) {
            file << current->data << std::endl;
            current = current->next;
        }
        file.close();
    }

private:
    Node<Data>* head;
    Node<Data>* tail;
};