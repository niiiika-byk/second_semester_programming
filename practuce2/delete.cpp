#include "delete.hpp"

class tableJson;

// поиск колонки
bool isColumnExist(const string& tableName, const string& columnName, Table* tableHead) { 
    Table* currentTable = tableHead; // указатель на голову структуры
    while (currentTable) {
        if (currentTable->table == tableName) {
            Column* currentColumn = currentTable->column;
            while (currentColumn) {
                if (currentColumn->column == columnName) { // есть ли колонка
                    return true;
                }
                currentColumn = currentColumn->next;
            }
            return false;
        }
        currentTable = currentTable->next;
    }
    return false;
}

// удаление
int del(const string& command, TableJson& tableJS) { 
    std::filesystem::path currentDirectory = std::filesystem::current_path();
    currentDirectory = currentDirectory.parent_path().string();
    string currentDir = currentDirectory.string();

    istringstream iss(command);
    string word;
    iss >> word;
    iss >> word;
    if (word != "FROM") {
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
    if (word != "WHERE") {
        cerr << "Incorrect command.\n";
        return 1;
    }

    iss >> word;
    string table, column;
    bool dot = false;
    for (size_t i = 0; i < word.size(); i++) {
        if (word[i] == '.') {
            dot = true;
            continue;
        }
        if (!dot) { // разделяем таблицу и колонку
            table += word[i];
        }
        else {
            column += word[i];
        }
    }
    if (!dot) {
        cerr << "Incorrect command.\n";
        return 1;
    }
    if (table != tableName) { // правильность таблицы
        cerr << "Incorrect command.\n";
        return 1;
    }
    if (isColumnExist(tableName, column, tableJS.tablehead) == false) {
        cerr << "There is no column.\n";
        return 1;
    }
    iss >> word;
    if (word != "=") {
        cerr << "Incorrect command.\n";
        return 1;
    }

    string value;
    iss >> word;
    if (word[0] != '\'' || word[word.size() - 1] != '\'') {
        cerr << "Incorrect command.\n";
        return 1;
    }
    for (size_t i = 1; i < word.size() - 1; i++) { // вытаскиваем значение из кавычек
        value += word[i];
    }

    if (is_locked(tableName, tableJS.schemeName) == true) {
        cerr << "Table is locked.\n";
        return 1;
    }
    locker(tableName, tableJS.schemeName); // блокировка

    int amountCsv = 1; //поиск scv
    while (true) {
        string filePath = currentDir + '/' + tableName + '/' + to_string(amountCsv) + ".csv";
        ifstream file(filePath);
        if (!file.is_open()) {
            break;
        }
        file.close();
        amountCsv++;
    }
    
    bool deletedStr = false; // существования значения
    for (size_t iCsv = 1; iCsv < amountCsv; iCsv++) {
        string filePath = currentDir + '/' + tableName + '/' + to_string(iCsv) + ".csv";
        rapidcsv::Document doc(filePath);
        int columnIndex = doc.GetColumnIdx(column);
        size_t amountRow = doc.GetRowCount();
        
        for (size_t i = 0; i < amountRow; ++i) { 
            if (doc.GetCell<string>(columnIndex, i) == value) {
                doc.RemoveRow(i); // удаляем строку
                deletedStr = true;
                --amountRow;
                --i;
            }
        }

        string pkFile = currentDir + "/" + tableName + "/" + tableName + "_pk_sequence.txt";
        ifstream fileIn(pkFile);
        if (!fileIn.is_open()) {
            cerr << "Failed to open file.\n";
            return 1;
        }
        int prevPk;
        fileIn >> prevPk; // сбросили предыдущее значение
        fileIn.close();

        size_t pastPk;
        size_t amountRow2 = doc.GetRowCount();
        if (amountRow2 == 0) {
            ofstream fileOut(pkFile);
            if (!fileOut.is_open()) {
                cerr << "Failed to open file.\n";
                return 1;
            }
            fileOut << "0"; // записываем новый ключ
            fileOut.close();
            break;
        }
        else {
            pastPk = doc.GetCell<int>(0, amountRow2 - 1);
            ofstream fileOut(pkFile);
            if (!fileOut.is_open()) {
                cerr << "Failed to open file.\n";
                return 1;
            }
            fileOut << pastPk; // записываем новый ключ
            fileOut.close();
        }
        doc.Save(filePath);
    }

    if (deletedStr == false) {
        cout << "Value not found.\n";
    }
    locker(tableName, tableJS.schemeName); // разблокировка
    return 0;
}