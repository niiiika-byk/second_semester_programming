#pragma once
#include <iostream>
#include "parser.hpp"
#include "insert.hpp"
#include "delete.hpp"

using namespace std;

// поиск точки
void splitDot(const string& word, string& table, string& column, TableJson& tableJS);
// отделение от кавычек строки
string ignoreQuotes(const string& word);
// наличие точки в слове
bool findDot(const string& word);
// количество созданных csv файлов
int countCsv(TableJson& tableJS, const string& table);
// объекдинение 2 таблиц
void crossJoin(TableJson& tableJS, const string& table1, const string& table2, const string& column1, const string& column2, char *buffer);
// проверка условий в таблицах
bool checkCond(TableJson& tableJS, const string& table, const string& column, const string& tcond, const string& ccond, const string& s);
// выборка
int select(char *buffer, int BUFFER_SIZE, TableJson& tableJS);
