#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include "struct_data_base.hpp"
#include "HashTable.hpp"

void command_processing(const Base_tables& base_tables) {
    std::cout << ">>> ";
    std::string SQLquery;
    getline(std::cin, SQLquery);
    LinkedList wordsFromQuery;
    std::string space = " ";
    size_t start = 0;
    size_t end = SQLquery.find(space);

    while (end != std::string::npos) {
        wordsFromQuery.push_back(SQLquery.substr(start, end - start));
        start = end + space.length();
        end = SQLquery.find(space, start);
    }
    wordsFromQuery.push_back(SQLquery.substr(start, end));

    if (wordsFromQuery.head->data == "SELECT" && wordsFromQuery.head->next->data == "FROM") {
        try {
            std::cout << "SELECT!" << std::endl;
            //ParseSelect(wordsFromQuery, fileDirectory, schemaName, JSONSchema);
        } catch (const std::exception& ErrorInfo) {
            std::cerr << ErrorInfo.what() << std::endl;
        }
    } 
    else if (wordsFromQuery.head->data == "INSERT" && wordsFromQuery.head->next->data == "INTO") {
        try {
            std::cout << "INSERT!" << std::endl;
            //ParsingInsert(wordsFromQuery, fileDirectory, schemaName, JSONSchema);
        } catch (const std::exception& ErrorInfo) {
            std::cerr << ErrorInfo.what() << std::endl;
        }
    } 
    else if (wordsFromQuery.head->data == "DELETE" && wordsFromQuery.head->next->data == "FROM") {
        try {
            std::cout << "DELETE!" << std::endl;
            //ParsingDelete(wordsFromQuery, fileDirectory, schemaName, JSONSchema);
        } catch (const std::exception& ErrorInfo) {
            std::cerr << ErrorInfo.what() << std::endl;
        }
    } 
    else {
        std::cout << "Неверная команда!" << std::endl;
    }
}