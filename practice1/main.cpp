#include <iostream>
#include <fstream>
#include <string>

#include "all_structures.hpp"
#include "create_files.hpp"

int main(){
    Base_tables base_tables;
    try {
        load_schema(base_tables, "schema.json");
        create_directories_and_files(base_tables);
        std::cout << "Files created" << std::endl;
        command_processing(base_tables);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}