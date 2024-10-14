#pragma once

#include <iostream>
#include "hash_table.hpp"

template <typename Key>
class Set{
private:
    Hash_map<Key, bool, 1> elements;

public:
    // Добавление элемента
    void add(const Key& value) {
        elements.insert(value, true); // Используем true как значение, чтобы обозначить наличие ключа
    }

    // Удаление элемента
    void remove(const Key& value) {
        elements.remove(value);
    }

    // Проверка, является ли элемент частью множества
    bool is_member(const Key& value) {
        return elements.get_value(value); // Если элемент существует, вернет true
    }

    // Вывод элементов множества
    void display() {
        elements.display(); // Вывод элементов из хэш-таблицы
    }

    void load_from_file(const std::string& filename) {
        elements.load_from_file(filename);
    }

    void save_to_file(const std::string& filename) {
        elements.save_to_file(filename);
    }
};