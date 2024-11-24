#include <queue>
#include <iostream>
#include <fstream>

#include "tree_node.hpp"

using namespace std;

class CBTree {
public: 
    CBTree() : root(nullptr) {}

    //добавление узла
    void insert(int digit) { 
        Tree_node* new_node = new Tree_node(digit); 
        if (root == nullptr) {
            root = new_node;
            return;
        }
        Queue_tree Q; 
        Q.enqueue(root);
        while (!Q.is_empty()) {
            Tree_node* current = Q.dequeue();
            if (current->left == nullptr) {
                current->left = new_node;
                return;
            }
            else {
                Q.enqueue(current->left);
            }
            if (current->right == nullptr) {
                current->right = new_node;
                return;
            }
            else {
                Q.enqueue(current->right);
            }
        }
    }

    // проверка на полное дерево
    bool is_CBT() { 
        if (root == nullptr) {
            cout << "Tree is empty.\n";
            return false;
        }

        Queue_tree Q;
        Q.enqueue(root);
        bool non_full_node = false; //отсутствие потомка
        while (!Q.is_empty()) {
            Tree_node* current = Q.dequeue();
            
            if (current->left) {
                if (non_full_node) {
                    return false;
                }
                Q.enqueue(current->left);
            }
            else {
                non_full_node = true;
            }

            if (current->right) {
                if (non_full_node) {
                    return false;
                }
                Q.enqueue(current->right);
            }
            else {
                non_full_node = true;
            }
        }
        return true;
    }

    // поиск элемента по значению
    bool find_value(Tree_node* current, int value) { 
        if (current == nullptr) {
            return false;
        }
        if (current->digit == value) {
            return true;
        }
        return find_value(current->left, value) || find_value(current->right, value);
    }

    // функция для main
    bool get_value(int value) {
        if (root == nullptr) { // если дерево пустое
            cout << "Tree is empty.\n";
            return false;
        }
        return find_value(root, value);
    }

    // чтение (поиск по индексу)
    void find_index(int index) {
        if (index < 0) {
            cout << "Invalid index.\n";
            return;
        }

        if (root == nullptr) {
            cout << "Tree is empty.\n";
            return;
        }

        Queue_tree Q;
        Q.enqueue(root);
        int currentIndex = 0; // текущий индекс

        while (!Q.is_empty()) {
            Tree_node* current = Q.dequeue();
            if (currentIndex == index) {
                cout << "Value: " << current->digit << endl;
                return;
            }
            currentIndex++;
            if (current->left) {
                Q.enqueue(current->left);
            }
            if (current->right) {
                Q.enqueue(current->right);
            }
        }
        cout << "Value not found.\n";
    }

    void serialize(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file for serialization");
        }

        if (root == nullptr) {
            file << "-1"; // Если дерево пустое
            file.close();
            return;
        }

        Queue_tree Q;
        Q.enqueue(root);
        while (!Q.is_empty()) {
            Tree_node* current = Q.dequeue();
            if (current != nullptr) {
                file << current->digit << " ";
                Q.enqueue(current->left);
                Q.enqueue(current->right);
            } else {
                file << "-1 "; // Используем -1 для обозначения отсутствующего узла
            }
        }
        file.close();
    }

    void deserialize(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file for deserialization");
        }

        root = nullptr; // Reset the tree
        queue<Tree_node**> Q; // Use a queue of pointers to pointers
        int value;

        while (file >> value) {
            Tree_node* new_node = nullptr;
            if (value != -1) {
                new_node = new Tree_node(value);
            }

            if (root == nullptr) {
                root = new_node; // Set the root
                Q.push(&root); // Add pointer to root in the queue
            } else {
                if (Q.empty()) {
                    throw runtime_error("Queue is empty, but more nodes are expected.");
                }
                Tree_node** parent_ptr = Q.front(); // Get pointer to parent node
                Q.pop();
                if ((*parent_ptr)->left == nullptr) {
                    (*parent_ptr)->left = new_node; // Set left child
                    Q.push(&((*parent_ptr)->left)); // Add pointer to left child in the queue
                } else {
                    (*parent_ptr)->right = new_node; // Set right child
                    Q.push(&((*parent_ptr)->right)); // Add pointer to right child in the queue
                }
            }
        }
        file.close();
    }

    // вывод обхода
    void print_CBT(Tree_node* current, int level) {
        if (current) {
            print_CBT(current->right, level + 1);
            for (int i = 0; i < level; i++) {
                cout << "   ";
            }

            cout << current->digit << endl; 
            print_CBT(current->left, level + 1);
        }
    }

    //вывод в консоль   
    void display() {
        if (root == nullptr) {
            cout << "Tree is empty.\n";
            return;
        }
        print_CBT (root, 0);
    }

private:
    Tree_node* root;
};