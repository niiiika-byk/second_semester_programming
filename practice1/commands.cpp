#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>

#include "all_structures.hpp"
#include "HashTable.hpp"

void command_processing (const Base_tables& base_tables) {
    std::cout << ">>> ";
    std::string SQLquery;
    getline(std::cin, SQLquery);
    LinkedList command;
    std::string space = " ";
    size_t start = 0;
    size_t end = SQLquery.find(space);

    while (end != std::string::npos) {
        command.push_back(SQLquery.substr(start, end - start));
        start = end + space.length();
        end = SQLquery.find(space, start);
    }
    command.push_back(SQLquery.substr(start, end));

    if (command.head->data == "INSERT" && command.head->next->data == "INTO") {
        try {
            std::string schema_name = command.head->next->next->data;
            std::string file_directory = base_tables.schema_name + "/" + schema_name;
            std::string file_name = command.head->next->next->data + "_1.csv";
            insert_to_table(schema_name, file_directory, file_name, base_tables);
        } catch (const std::exception& ErrorInfo) {
            std::cerr << ErrorInfo.what() << std::endl;
        }

    } else if (command.head->data == "DELETE" && command.head->next->data == "FROM") {
        try {
            std::cout << "DELETE!" << std::endl;
            //ParsingDelete(wordsFromQuery, fileDirectory, schemaName, JSONSchema);
        } catch (const std::exception& ErrorInfo) {
            std::cerr << ErrorInfo.what() << std::endl;
        }

    } else if (command.head->data == "SELECT" && command.head->next->data == "FROM") {
        try {
            std::cout << "SELECT!" << std::endl;
            //ParseSelect(wordsFromQuery, fileDirectory, schemaName, JSONSchema);
        } catch (const std::exception& ErrorInfo) {
            std::cerr << ErrorInfo.what() << std::endl;
        }
    }    
    else {
        std::cout << "Неверная команда!" << std::endl;
    }
}