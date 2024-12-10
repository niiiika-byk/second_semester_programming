#include "insert.hpp"

// проверка блокировки таблицы
bool is_locked(const string& tableName, const string& schemeName) { 
    std::filesystem::path currentDirectory = std::filesystem::current_path();
    currentDirectory = currentDirectory.parent_path().string();
    string currentDir = currentDirectory.string();
    string fileName = currentDir + "/" + tableName + "/" + tableName + "_lock.txt";

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Failed to open file.\n";
    }
    string current;
    file >> current;
    file.close();
    if (current == "locked") {
        return true;
    }
    return false;
}

// изменение состояния блокировки
void locker(const string& tableName, const string& schemeName) { 
    std::filesystem::path currentDirectory = std::filesystem::current_path();
    currentDirectory = currentDirectory.parent_path().string();
    string currentDir = currentDirectory.string();
    string fileName = currentDir + "/"+ tableName + "/" + tableName + "_lock.txt";

    ifstream fileIn(fileName);
    if (!fileIn.is_open()) {
        cerr << "Failed to open file.\n";
        return;
    }
    string current;
    fileIn >> current;
    fileIn.close();

    ofstream fileOut(fileName);
    if (!fileOut.is_open()) {
        cerr << "Failed to open file.\n";
        return;
    }
    if (current == "locked") {
        fileOut << "unlocked";
    } else {
        fileOut << "locked";
    }
    fileOut.close();
}

// проверка: существует ли таблица
bool isTableExist(const string& tableName, Table* tableHead) { 
    Table* current = tableHead;
    while (current) {
        if (current->table == tableName) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// копирование названия колонок
void copyColumnsName(const string& fileFrom, const string& fileTo) { 
    string columns;
    ifstream fileF(fileFrom);
    if (!fileF.is_open()) {
        cerr << "Failed to open file.\n";
        return;
    }
    fileF >> columns;
    fileF.close();
    ofstream fileT(fileTo);
    if (!fileT.is_open()) {
        cerr << "Failed to open file.\n";
        return;
    }
    fileT << columns << endl;
    fileT.close();
}

// вставка
int insert(const string& command, TableJson& tableJS) { 
    std::filesystem::path currentDirectory = std::filesystem::current_path();
    currentDirectory = currentDirectory.parent_path().string();
    string currentDir = currentDirectory.string();

    istringstream iss(command);
    string word;
    iss >> word;
    iss >> word;
    if (word != "INTO") {
        cerr << "Incorrect command.\n";
        return 1;
    }
    string tableName;
    iss >> word;
    if (isTableExist(word, tableJS.tablehead) == false) {
        cerr << "There is no table.\n";
        return 1;
    }
    tableName = word;
    iss >> word;
    if (word != "VALUES") {
        cerr << "Incorrect command.\n";
        return 1;
    }

    std::string values;
    std::getline(iss, values);
    size_t start = values.find('(');
    size_t end = values.rfind(')');
    if (start == std::string::npos || end == std::string::npos || start >= end) {
        std::cerr << "Incorrect command format.\n";
        return 1;
    }
    values = values.substr(start + 1, end - start - 1);

    // Разделяем значения на группы для множественной вставки
    std::string valueSet;
    std::istringstream valuesStream(values);
    std::vector<std::string> records;

    while (std::getline(valuesStream, valueSet, ')')) {
        size_t start = valueSet.find('(');
        if (start != std::string::npos) {
            valueSet = valueSet.substr(start + 1);
        }

        if (!valueSet.empty()) {
            records.push_back(valueSet); // Добавляем запись в вектор
        }
    }

    if (is_locked(tableName, tableJS.schemeName)) {
        std::cerr << "Table is locked.\n";
        return 1;
    }
    locker(tableName, tableJS.schemeName); // Проверка блокировки

    for (const auto& record : records) {
        int currentPk;
        std::string pkFile = currentDir + "/" + tableName + "/" + tableName + "_pk_sequence.txt";
        std::ifstream pkIn(pkFile);
        if (!pkIn.is_open()) {
            std::cerr << "Failed to open primary key file: " << pkFile << std::endl;
            locker(tableName, tableJS.schemeName); // Разблокируем в случае ошибки
            return 1;
        }
        pkIn >> currentPk;
        pkIn.close();

        std::ofstream pkOut(pkFile);
        if (!pkOut.is_open()) {
            std::cerr << "Failed to open primary key file for writing: " << pkFile << std::endl;
            locker(tableName, tableJS.schemeName); // Разблокируем в случае ошибки
            return 1;
        }
        pkOut << ++currentPk;

        int csvNum = 1;
        std::string csvFile;
        while (true) {
            csvFile = currentDir + "/" + tableName + "/" + std::to_string(csvNum) + ".csv";
            std::ifstream file(csvFile);
            if (file.peek() == std::ifstream::traits_type::eof() || std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n') < tableJS.tableSize) {
                break;
            }
            csvNum++;
        }

        std::ofstream csvOut(csvFile, std::ios::app);
        if (!csvOut.is_open()) {
            std::cerr << "Failed to open CSV file: " << csvFile << std::endl;
            locker(tableName, tableJS.schemeName); // Разблокируем в случае ошибки
            return 1;
        }
        csvOut << currentPk << ","; // Записываем текущий первичный ключ

        // Обработка значений для вставки
        size_t endPos = 0;
        for (size_t i = 0; i < record.length(); i++) {
            if (record[i] == ',' && (i == 0 || record[i - 1] != '\'')) {
                std::string currentValue = record.substr(endPos, i - endPos);
                csvOut << currentValue << ",";
                endPos = i + 1;
            } else if (record[i] == '\'' && (i == 0 || record[i - 1] != '\\')) {
                // Игнорируем одинарные кавычки
                continue;
            }
        }
        // Записываем последнее значение
        std::string lastValue = record.substr(endPos);
        csvOut << lastValue << std::endl;

        locker(tableName, tableJS.schemeName); // Разблокировка после вставки
    }
    return 0;
}