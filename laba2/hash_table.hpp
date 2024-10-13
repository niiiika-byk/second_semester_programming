#include "hash_node.hpp"
#include "hash_function.hpp"
#include <iostream>
#include <fstream>

template <typename Key, typename Value, unsigned long table_size,typename Hash_func = Hash_function<Key>>
class Hash_map {
public:
    Hash_node<Key, Value>* table[table_size];
    Hash_func hash;

    Hash_map() {
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

    void insert(const Key &key, const Value &value) {
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

    /*void clear() {
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
            Value value;
            iss >> key >> value;
            insert(key, value);
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
            Hash_node<Key, Value> *entry = table[i];
            while (entry != nullptr) {
                file << entry->get_key() << " " << entry->get_value() << std::endl;
                entry = entry->get_next();
            }
        }

        file.close();
    }*/
};