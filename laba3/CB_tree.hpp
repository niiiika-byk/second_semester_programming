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

    void clear(Tree_node*& node) {
        if (node) {
            clear(node->left);
            clear(node->right);

            delete node;
            node = nullptr;
        }
    }

    void load_from_file(const string& file) { 
        clear(root);
        ifstream load(file);
        if (!load) {
            cout << "Failed open file.\n";
            return;
        }

        int value;
        while (load >> value) {
            insert(value);
        }
        load.close();
    }

    void save_from_file(const string& file) {
        ofstream save(file);
        if (!save) {
            cout << "Failed open file.\n";
            return;
        }

        Queue_tree Q;
        Q.enqueue(root); // начинаем обход с корня
        while (!Q.is_empty()) {
            Tree_node* current = Q.dequeue(); // текущий узел
            save << current->digit << endl; 
            if (current->left) { // левый потомок
                Q.enqueue(current->left);
            }
            if (current->right) { // правый потомок
                Q.enqueue(current->right);
            }
        }
        save.close();
    }

private:
    Tree_node* root;
};