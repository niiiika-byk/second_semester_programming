#pragma once

class Tree_node {
public:
    Tree_node(int dig) : digit(dig), left(nullptr), right(nullptr) {}
    friend class Queue_tree;
    friend class Queue_node;
    friend class CBTree;
    
private:
    int digit;
    Tree_node* left;
    Tree_node* right;
};

struct Queue_node {
    Tree_node* tree;
    Queue_node* next;
};

class Queue_tree { 
public:
    Queue_tree() : front(nullptr), rear(nullptr), count(0) {}
    friend class CBTree;

    bool is_empty() {
        return count == 0;
    }

    void enqueue(Tree_node* node) { // добавление узла в очередь
        Queue_node* new_node = new Queue_node();
        new_node->tree = node;
        new_node->next = nullptr;

        if (rear == nullptr) {
            front = rear = new_node;
        }
        else {
            rear->next = new_node;
            rear = new_node;
        }

        count++;
    }

    Tree_node* dequeue() {
        if (is_empty()) {
            return nullptr;
        }

        Queue_node* new_node = front;
        Tree_node* res = front->tree; 
        front = front->next;
        
        if (front == nullptr) {
            rear = nullptr;
        }

        delete new_node;
        count--;
        return res;
    }

private:
    Queue_node* front;
    Queue_node* rear;
    int count;
};