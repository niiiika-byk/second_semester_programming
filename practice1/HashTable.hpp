#pragma once

#include "hash_function.hpp"
#include <iostream>

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

template <typename Key, typename Value, unsigned long table_size,typename Hash_func = Hash_function<Key>>
class Hash_map {
public:
    Hash_node<Key, Value>* table[table_size];
    Hash_func hash;

    Hash_map(){
        for (int i = 0; i < table_size; i++) {
            table[i] = nullptr;
        }    
    }
    ~Hash_map() {
        for (unsigned long i = 0; i < table_size; i++) {
            Hash_node<Key, Value> *entry = table[i];
            while (entry != nullptr) {
                Hash_node<Key, Value> *prev = entry;
                entry = entry->get_next();
                delete prev;

            }
        }
    }

    Value get_value(const Key &key) {
        unsigned long hash_value = hash(key, table_size);
        Hash_node<Key, Value>* entry = table[hash_value];

        while (entry != nullptr) {
            if (entry->get_key() == key) {
                return entry->get_value();
            }
            entry = entry->get_next();
        }
        return Value();
    }

    void insert(const Key &key, const Value &value)
    {
        unsigned long hash_value = hash(key, table_size);
        Hash_node<Key, Value> *prev = nullptr;
        Hash_node<Key, Value> *entry = table[hash_value];

        while (entry != nullptr && entry->get_key() != key) {
            prev = entry;
            entry = entry->get_next();
        }

        if (entry == nullptr) {
            entry = new Hash_node<Key, Value>(key, value);

            if (prev == nullptr) {
                table[hash_value] = entry;

            } else {
                prev->set_next(entry);
            }

        } else {
            
            entry->set_value(value);
        }
    }

    void remove(const Key &key) {
        unsigned long hash_value = hash(key, table_size);
        Hash_node<Key, Value> *prev = nullptr;
        Hash_node<Key, Value> *entry = table[hash_value];

        while (entry != nullptr) {
            if(entry->get_key() != key){
                prev = entry;
                entry = entry->get_next();
            } else {
                break;
            }
        }

        if (entry == nullptr) {
            return;

        } else {
            if (prev == nullptr) {
                table[hash_value] = entry->get_next();

            } else {
                prev->set_next(entry->get_next());
            }

            delete entry;
        }
    }
    
    void display() {
        for (unsigned long i = 0; i < table_size; i++) {
            Hash_node<Key, Value> *entry = table[i];
            while (entry != nullptr) {
                std::cout << "Key: " << entry->get_key() << ", Value: " << entry->get_value() << std::endl;
                entry = entry->get_next();
            }
        }
    }

    void clear() {
        for (unsigned long i = 0; i < table_size; i++) {
            Hash_node<Key, Value> *entry = table[i];
            while (entry != nullptr) {
                Hash_node<Key, Value> *prev = entry;
                entry = entry->get_next();
                delete prev;
            }
            table[i] = nullptr;
        }
    }
};