#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "json.hpp"

using namespace std;

class Column { // список колонок
public:
    std::string column;
    Column* next;

    Column(const std::string& column, Column* next) : column(column), next(next) {}
    ~Column() {
        Column* current = this;
        while (current) {
            Column* next = current->next;
            delete current;
            current = next;
        }
    }
};

class Table { // список таблиц
public:
    std::string table;
    Column* column;
    Table* next;

    Table(const std::string& table, Column* column, Table* next) : table(table), column(column), next(next) {}
    ~Table() {
        Table* current = this;
        while (current) {
            Table* next = current->next;
            delete current;
            current = next;
        }
    }
};
class TableJson {
public:
    int tableSize;
    string schemeName;
    Table* tablehead;
};

// удаление директории
void removeDirectory(const std::filesystem::path& directoryPath);
// создание директорий и файлов
void createDirectoriesAndFiles(const std::filesystem::path& schemePath, const nlohmann::json& structure, TableJson& tableJS);
// парсинг схемы
void parsing(TableJson& tableJS); 