#pragma once

#include <iostream>
#include <fstream>
#include "set_node.hpp"
#include "hash_function.hpp"

template <typename Key, unsigned long table_size,typename Hash_func = Hash_function<Key>>
class Set{
public:

    Set_node<Key>* table[table_size];
    Hash_func hash;
    int capacity_size = 0;

    Set() {
        for (int i = 0; i < table_size; i++) {
            table[i] = nullptr;
        }    
    }
    ~Set() {
        for (unsigned long i = 0; i < table_size; i++) {
            Set_node<Key> *entry = table[i];
            while (entry != nullptr) {
                Set_node<Key> *prev = entry;
                entry = entry->get_next();
                delete prev;

            }
        }
    }

    Key get_value(const Key &key) {
        unsigned long hash_value = hash(key, table_size);
        Set_node<Key>* entry = table[hash_value];

        while (entry != nullptr) {
            if (entry->get_key() == key) {
                return entry->get_key();
            }
            entry = entry->get_next();
        }
        return Key();
    }

    void add(const Key &key){
        unsigned long hash_value = hash(key, table_size);
        Set_node<Key> *prev = nullptr;
        Set_node<Key> *entry = table[hash_value];

        while (entry != nullptr && entry->get_key() != key) {
            prev = entry;
            entry = entry->get_next();
        }

        if (entry == nullptr) {
            entry = new Set_node<Key>(key);
            capacity_size++;
            if (prev == nullptr) {
                table[hash_value] = entry;

            } else {
                prev->set_next(entry);
            }

        }
    }

    void remove(const Key &key) {
        unsigned long hash_value = hash(key, table_size);
        Set_node<Key> *prev = nullptr;
        Set_node<Key> *entry = table[hash_value];

        while (entry != nullptr && entry->get_key() != key) {
            prev = entry;
            entry = entry->get_next();
        }

        if (entry == nullptr) {
            return;

        } else {
            if (prev == nullptr) {
                table[hash_value] = entry->get_next();

            } else {
                prev->set_next(entry->get_next());
            }

            capacity_size--;
            delete entry;
        }
    }
    
    void display() {
        for (unsigned long i = 0; i < table_size; i++) {
            Set_node<Key> *entry = table[i];
            while (entry != nullptr) {
                std::cout << entry->get_key() << " ";
                entry = entry->get_next();
            }
        }
        std::cout << std::endl;
    }
    
    void clear() {
        for (unsigned long i = 0; i < table_size; i++) {
            Set_node<Key> *entry = table[i];
            while (entry != nullptr) {
                Set_node<Key> *prev = entry;
                entry = entry->get_next();
                delete prev;
            }
            table[i] = nullptr;
        }
    }

    void load_from_file(const std::string &filename) {
        clear();
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed open file" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Key key;
            iss >> key;
            add(key);
        }

        file.close();
    }

    void save_to_file(const std::string &filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed open file" << std::endl;
            return;
        }

        for (unsigned long i = 0; i < table_size; i++) {
            Set_node<Key> *entry = table[i];
            while (entry != nullptr) {
                file << entry->get_key() << std::endl;
                entry = entry->get_next();
            }
        }

        file.close();
    }

    void get_all_elements(Set_node<Key>* elements[], int &count) {
        count = 0; // Сброс счётчика
        
        for (unsigned long i = 0; i < table_size; i++) {
            Set_node<Key>* entry = table[i];
            while (entry != nullptr) {
                elements[count++] = entry; // Сохраняем указатель на элемент
                entry = entry->get_next();
            }
        }
    }
};