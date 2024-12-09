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
    string values;
    while (iss >> word) {
        values += word;
    }
    if (values.front() != '(' || values.back() != ')') {
        cerr << "Incorrect command.\n";
        return 1;
    }


    if (is_locked(tableName, tableJS.schemeName) == true) {
        cerr << "Table is locked.\n";
        return 1;
    }
    locker(tableName, tableJS.schemeName); //проверка блокировки

    int currentPk;
    string pkFile = currentDir + "/" + tableName + "/" + tableName + "_pk_sequence.txt";
    ifstream fileIn(pkFile);
    if (!fileIn.is_open()) {
        cerr << "Failed to open file.\n";
        return 1;
    }
    fileIn >> currentPk;
    fileIn.close();
    ofstream fileOut(pkFile);
    if (!fileOut.is_open()) {
        cerr << "Failed to open file.\n";
        return 1;
    }
    currentPk++;
    fileOut << currentPk; // записываем новый ключ
    fileOut.close();

    int csvNum = 1; // номер файла csv
    while (true) {
        string csvFile = currentDir + "/" + tableName + "/" + to_string(csvNum) + ".csv";
        ifstream fileIn(csvFile);
        if (!fileIn.is_open()) {
            ofstream fileOut(csvFile);
            if (!fileOut.is_open()) {
                cerr << "Failed to open file.\n";
                return 1;
            }
            fileOut.close();
        }
        else {
            fileIn.close();
        }
        rapidcsv::Document doc(csvFile); // считываем csv, если csv полон
        if (doc.GetRowCount() < tableJS.tableSize) {
            break;
        }
        csvNum++;
    }

    string csvOne = currentDir + "/" + tableName + "/1.csv";
    string csvF = currentDir + "/" + tableName + "/" + to_string(csvNum) + ".csv";
    
    rapidcsv::Document doc_(csvF);
    if (doc_.GetRowCount() == 0 && doc_.GetColumnCount() == 0) {
        copyColumnsName(csvOne, csvF);
    }
    ofstream csv(csvF, ios::app);
    if (!csv.is_open()) {
        cerr << "Failed to open file.\n";
        return 1;
    }
    csv << currentPk << ","; // записываем текущий первичный ключ
    for (int i = 0; i < values.size(); i++) {
        if (values[i] == '\'') {
            i++;
            while (values[i] != '\'') {
                csv << values[i];
                i++;
            }
            if (values[i + 1] != ')') {
                csv << ",";
            }
            else {
                csv << endl;
            }
        }
    }
    csv.close();
    locker(tableName, tableJS.schemeName); // разблокировка
    return 0;
}