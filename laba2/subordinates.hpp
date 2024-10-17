#include <iostream>

#include "hash_table.hpp"

int count_subordinates(const Hash_map<std::string, std::string, 1>& table, const std::string& manager) {
    int count = 0;

    Hash_node<std::string, std::string>* entry = table.table[0];
    while (entry != nullptr) {
        std::string employee = entry->get_key(); // получаем ключ сотрудника
        std::string supervisor = entry->get_value(); // получаем менеджера сотрудника
        if (supervisor == manager) {
            count++; // увеличиваем счетчик, если сотрудник является подчиненным менеджера
            count += count_subordinates(table, employee); // Рекурсивно считаем подчиненных
        }
        entry = entry->get_next();
    }

    return count;
}

void subordinates(const Hash_map<std::string, std::string, 1>& table, Hash_map<std::string, int, 1>& count_table) {
    Hash_node<std::string, std::string>* entry = table.table[0];
    int count = 0;
    while (entry != nullptr) {
        std::string manager = entry->get_value();
        int count = count_subordinates(table, manager);
        count_table.insert(manager, count);
        entry = entry->get_next();
    }
}