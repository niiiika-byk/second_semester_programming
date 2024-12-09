#include "parser.hpp"

// удаление директории
void removeDirectory(const std::filesystem::path& directoryPath) { 
    if (std::filesystem::exists(directoryPath)) {
        std::filesystem::remove_all(directoryPath);
    }
}

// создание полной директории и файлов
void createDirectoriesAndFiles(const std::filesystem::path& schemePath, const nlohmann::json& structure, TableJson& tjs) { 
    Table* tableHead = nullptr;
    Table* tableTail = nullptr;

    for (const auto& table : structure.items()) {
        std::filesystem::path tablePath = schemePath / table.key();
        if (!std::filesystem::create_directory(tablePath)) {
            cerr << "Failed to create a directory: " << tablePath << endl;
            return;
        }

        Table* newTable = new Table{table.key(), nullptr, nullptr};

        std::filesystem::current_path(tablePath);

        string lock = table.key() + "_lock.txt"; //блокировочный файл
        ofstream file(lock);
        if (!file.is_open()) {
            cerr << "Failed to open a file.\n";
        }
        file << "unlocked";
        file.close();

        if (tableHead == nullptr) { // добавляем таблицу в список
            tableHead = newTable;
            tableTail = newTable;
        }
        else {
            tableTail->next = newTable;
            tableTail = newTable; 
        }

        string keyColumn = table.key() + "_pk"; // список колонок с id
        Column* column_pk = new Column{keyColumn, nullptr};
        newTable->column = column_pk;

        std::filesystem::path csvFilePath = tablePath / "1.csv"; // csv
        ofstream csvFile(csvFilePath);
        if (!csvFile.is_open()) {
            cerr << "Failed to create a file: " << csvFilePath << endl;
            return;
        }

        csvFile << keyColumn << ",";
        const auto& columns = table.value(); // запись колонок
        
        for (size_t i = 0; i < columns.size(); ++i) { 
            csvFile << columns[i].get<string>();
            Column* newColumn = new Column{columns[i], nullptr};
            if (newTable->column == nullptr) {
                newTable->column = newColumn;
            }
            else {
                Column* lastColumn = newTable->column;
                while (lastColumn->next != nullptr) {
                    lastColumn = lastColumn->next;
                }
                lastColumn->next = newColumn;
            }
            if (i < columns.size() - 1) {
                csvFile << ",";
            }
        }
        csvFile << endl;
        csvFile.close();

        string pk = keyColumn + "_sequence.txt"; // файл с последним id
        ofstream filePk(pk);
        if (!filePk.is_open()) {
            cerr << "Failed to open a file.\n";
        }
        filePk << "0";
        filePk.close();
    }
    tjs.tablehead = tableHead;
}

// парсинг схемы
void parsing(TableJson& tableJS) { 
    string filename = "schema.json";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open a file. " << filename << endl;
        return;
    }

    string json_content; // содержимое
    string line;

    while(getline(file, line)) {
        json_content += line;
    }
    file.close();

    nlohmann::json jparsed;
    jparsed = nlohmann::json::parse(json_content);

    tableJS.schemeName = jparsed["name"];
    std::filesystem::path schemePath = std::filesystem::current_path() / tableJS.schemeName;

    removeDirectory(schemePath); // заново создать директорию

    if (!std::filesystem::create_directory(schemePath)) {
        cerr << "Failed to create a directory: " << schemePath << endl;
        return;
    }
    
    tableJS.tableSize = jparsed["tuples_limit"];

    if (jparsed.contains("structure")) {
        createDirectoriesAndFiles(schemePath, jparsed["structure"], tableJS);
    }  
    cout << "Create a full directory: " << schemePath << endl;
}