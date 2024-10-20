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
    Node* LinkedList::search_value(std::string value);
    void display();
    void clear();
};

template <typename Key, typename Value>
class Hash_node {
public:
    Key _key;
    Value _value;
    Hash_node* _next;
    
    Hash_node(const Hash_node &) = delete;      //конструктор копирования запрещен
    Hash_node & operator=(const Hash_node &) = delete; //оператор присваивания запрещен

    Hash_node(const Key &key, const Value &value) :
        _key(key), _value(value), _next(nullptr){}

    Key get_key() const{
        return _key;
    }

    Value get_value() const {
        return _value;
    }

    void set_value(Value value) {
        _value = value;
    }

    Hash_node* get_next() const {
        return _next;
    }

    void set_next(Hash_node *next) {
        _next = next;
    }
};

class Table{
public:
    std::string table_name;
    LinkedList column_name;
    int tuples;

    Hash_map<std::string, std::string, 1> table_values;
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
};

void load_schema(Base_tables& base_tables, const std::string& name_json);

void create_csv(const std::string& dir_table, Table& table, int tuples_limit);

void create_key_file(const std::string& dir_table, const std::string& table_name);

void create_lock_file(const std::string& dir_table, const std::string& table_name);

void command_processing(const Base_tables& base_tables);

void create_directories_and_files(const Base_tables& base_tables);