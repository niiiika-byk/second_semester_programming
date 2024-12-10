#pragma once
#include <iostream>
#include "parser.hpp"
#include "insert.hpp"
#include "delete.hpp"

using namespace std;

struct Condition {
    std::string column;
    std::string op;
    std::string value;
};

// Удаление префикса таблицы и очистка от лишних пробелов
std::string removeTablePrefix(const std::string& columnName);
// Функция для очистки значения от кавычек и пробелов
std::string cleanValue(std::string val);
// Проверка условий WHERE
bool checkCondition(const std::string& cellValue, const std::string& condition, const std::string& op);
// Парсинг одного условия
void parseSingleCondition(const std::string& combined, std::vector<Condition>& conditions);
// Парсинг условий
void parseConditions(const std::string& conditionStr, std::vector<Condition>& conditions, std::vector<std::string>& logicOps);
// Функция проверки всех условий по логическим связкам
bool checkAllConditions(const std::vector<Condition>& conditions,
                        const std::vector<std::string>& headers,
                        const std::vector<std::string>& rowValues,
                        const std::vector<std::string>& logicOps);
// Функция парсинга условий из строки после WHERE
void selectFromTables(const std::string& command, TableJson& tableJS);
