#pragma once
#include <iostream>
#include <filesystem>
#include "parser.hpp"
#include "rapidcsv.hpp"

using namespace std;

// проверка блокировки таблицы
bool is_locked(const std::string& tableName, const std::string& schemeName); 
// изменение состояния блокировки
void locker(const std::string& tableName, const std::string& schemeName); 
// проверка: существует ли таблица
bool isTableExist(const std::string& tableName, Table* tableHead); 
// копирование названия колонок
void copyColumnsName(const std::string& fileFrom, const std::string& fileTo); 
// вставка
void insert(const std::string& command, struct TableJson & tableJS);