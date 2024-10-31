#pragma once
#include <iostream>
#include <fstream>
#include "insert.hpp"

using namespace std;

// удаление
int del(const string& command, TableJson& tableJS); 
// поиск колонки
bool isColumnExist(const string& tableName, const string& columnName, Table* tableHead);