#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <ostream>
#include <filesystem>

#include "all_structures.hpp"
#include "json.hpp"

void load_schema(Base_tables& base_tables, const std::string& name_json) {
    std::ifstream file(name_json);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open schema.json");
    }

    nlohmann::json schema;
    file >> schema;
    base_tables.schema_name = schema["name"];
    base_tables.tuples_limit = schema["tuples_limit"];

    // Заполнение списка таблиц
    for (const auto& table : schema["structure"].items()) {
        Table tempTable; 
        tempTable.table_name = table.key();

        // Заполнение списка колонок
        tempTable.column_name.clear();

        for (const std::string& column : table.value()) {
            tempTable.column_name.push_back(column);
        }

        base_tables.tables.push_back_table(tempTable);
    }
    
    file.close();
}

void create_directories_and_files(const Base_tables& base_tables) {
    if (!std::filesystem::exists(base_tables.schema_name)) {
        std::filesystem::create_directory(base_tables.schema_name);
    }
    
    Table_Node* current = base_tables.tables.head;
    while (current != nullptr) {
        std::string dir_table = base_tables.schema_name + "/" + current->data.table_name;
        if (!std::filesystem::exists(dir_table)) {
            std::filesystem::create_directory(dir_table);
        }
        create_csv(dir_table, current->data, base_tables.tuples_limit);

        create_key_file(dir_table, current->data.table_name);

        create_lock_file(dir_table, current->data.table_name);
        
        current = current->next;
    }
}

void create_csv(const std::string& dir_table, Table& table, int tuples_limit) {
    int fileIndex = 1;
    std::filesystem::path csvPath = std::filesystem::path(dir_table) / (table.table_name + "_" + std::to_string(fileIndex) + ".csv");
    
    std::ofstream csvFile(csvPath);
    if (!csvFile.is_open()) {
        std::cerr << "Error creating a CSV file in " << std::filesystem::absolute(csvPath) << std::endl;
        return;
    }

    csvFile << table.table_name << "_pk";

    Node* currentColumn = table.column_name.head;
    while (currentColumn != nullptr) {
        csvFile << "," << currentColumn->data;
        currentColumn = currentColumn->next;
    }
    
    csvFile << "\n";
    csvFile.close();
}

void create_key_file(const std::string& dir_table, const std::string& table_name) {
    std::ofstream pkFile(std::filesystem::path(dir_table) / (table_name + "_pk_sequence.txt"));
    if (!pkFile.is_open()) {
        std::cerr << "Impossible to create a primary key for " << table_name << std::endl;
        return;
    }

    pkFile << 0; // Начальное значение первичного ключа
    pkFile.close();
}

void create_lock_file(const std::string& dir_table, const std::string& table_name) {
    std::ofstream lockFile(std::filesystem::path(dir_table) / (table_name + "_lock.txt"));
    if (!lockFile.is_open()) {
        std::cerr << "Impossible to create a lock file" << table_name << std::endl;
        return;
    }

    lockFile << "Not blocked"; // Статус блокировки
    lockFile.close();
}