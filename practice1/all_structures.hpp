#pragma once
#include <string>
#include "HashTable.hpp"

#include "json.hpp"
#pragma once

namespace fs = std::filesystem;
using json = nlohmann::json;

class Node {
    public:
        std::string data; //поля объекта
        Node* next;
        Node* prev;

        Node(const std::string& value, Node* nextNode = nullptr, Node* prevNode = nullptr) //аргументы, = дефолтный аргументы
            : data(value), next(nextNode), prev(prevNode) {
        }
};

class LinkedList{
public:
    Node* head;
    Node* tail;

    LinkedList() : head(nullptr), tail(nullptr) {};
    ~LinkedList() {
        while (this->head != nullptr) {
            Node* next = this->head->next;
            delete this->head;
            this->head = next;
        }
    }

    void push_front(const std::string& value);
    void push_back(const std::string& value);
    void insert(int index, const std::string& value);
    void pop_head();
    void pop_tail();
    void pop(int index);
    void pop_value(const std::string& value);
    Node* search_value(std::string value);
    void display();
    void clear();
};

class Table{
public:
    std::string table_name;
    LinkedList column_name;
    int tuples;

    Hash_map<std::string, std::string, 1> table_values;

    ~Table() {
        while (this->column_name.head != nullptr) {
            Node* next = this->column_name.head->next;
            delete this->column_name.head;
            this->column_name.head = next;
        }
    }
};

class Table_Node {
public:
    Table data;
    Table_Node* next;
    Table_Node* prev;

    Table_Node(const Table& value, Table_Node* nextNode = nullptr, Table_Node* prevNode = nullptr)
        : data(value), next(nextNode), prev(prevNode) {
    }
};

class TablesLinkedList{
public: 
    Table_Node* head;
    Table_Node* tail;

    TablesLinkedList() : head(nullptr), tail(nullptr) {}

    ~TablesLinkedList() {
        while (this->head != nullptr) {
            Table_Node* next = this->head->next;
            delete this->head;
            this->head = next;
        }
    }

    void push_front_table(Table value);
    void push_back_table(Table value);
    void pop_head_table();
    void pop_tail_table();
    void pop_value_table(Table value);
    void search_value_table(Table value);
    Table_Node* return_value_table(Table value); // возвращаем ссылку на элемент по значению
    void displayUni();
    
};

class Base_tables {  //схема всех таблиц
public:
    std::string schema_name;
    int tuples_limit;
    TablesLinkedList tables;
    
    Hash_map<std::string, std::string, 1> hash_table_columns;  // Хеш-таблица для хранения колонок

    ~Base_tables() {
        while (this->tables.head != nullptr) {
            Table_Node* next = this->tables.head->next;
            delete this->tables.head;
            this->tables.head = next;
        }
    }
};

void load_schema(Base_tables& base_tables, const std::string& name_json);

void create_csv(const std::string& dir_table, Table& table, int tuples_limit);

void create_key_file(const std::string& dir_table, const std::string& table_name);

void create_lock_file(const std::string& dir_table, const std::string& table_name);

void command_processing(const Base_tables& base_tables);

void create_directories_and_files(const Base_tables& base_tables);

void insert_to_table(std::string schema_name, std::string file_directory, std::string file_name, const Base_tables& base_tables);