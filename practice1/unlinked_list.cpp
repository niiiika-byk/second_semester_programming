#include <string>
#include <iostream>
#include "struct_data_base.hpp"

using namespace std;

void TablesLinkedList::push_front_table(Table value){
    Table_Node* newNode = new Table_Node(value);
    if (head == nullptr){
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

void TablesLinkedList::push_back_table(Table value){
    Table_Node* newNode = new Table_Node(value);
    if (head == nullptr){
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void TablesLinkedList::pop_head_table(){
    if (head == nullptr){
        cout << "List is empty" << endl;
        return;
    } else{
        Table_Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void TablesLinkedList::pop_tail_table(){
    if (head == nullptr){
        cout << "List is empty" << endl;
        return;
    }
    if (head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Table_Node* current = head;
    while (current->next != tail){
        current = current->next;
    }
    current->next = nullptr;
   
    delete tail;
    tail = current;
}

void TablesLinkedList::pop_value_table(Table value){
    if (head == nullptr){
        cout << "List is empty" << endl;
        return;
    }
    if (value.table_name == head->data.table_name){
        pop_head_table();
        return;
    }
    if (value.table_name == tail->data.table_name){
        pop_tail_table();
        return;
    }
    Table_Node* current = head;
    while (current->next && current->next->data.table_name != value.table_name){
   
        current = current->next;
    }
    if (current->next == nullptr){
        cout << "Not found in list" << endl;
        return;
    }
    Table_Node* temp = current->next;
    current->next = temp->next;
    delete temp;
}

void TablesLinkedList::search_value_table(Table value){ // поиск элемента по значению
    Table_Node* current = head;
    while (current->next && current->data.table_name != value.table_name) {
        current = current->next;
    }
    if (current->data.table_name == value.table_name){
        cout << "Value " << current->data.table_name << " in list" << endl;
    } else {
        cout << "Value " << current->data.table_name << " not in list" << endl;
    }
}

Table_Node* TablesLinkedList::return_value_table(Table value){
    Table_Node* current = head;
    while (current->next && current->data.table_name != value.table_name) {
        current = current->next;
    }
    if (current->data.table_name == value.table_name){
        return current;
    } else {
        return nullptr;
    }
}

void TablesLinkedList::displayUni(){
    Table_Node* current = head;
    while (current != nullptr) {
        cout << current->data.table_name << " ";
        current = current->next;
    }
    cout << endl;
}