#include <iostream>

#include "hash_table.hpp"
#include "subordinates.hpp"

int main(){
    std::cout << "------------Task 1-----------" << std::endl;


    std::cout << "------------Task 3-----------" << std::endl;


    std::cout << "------------Task 4-----------" << std::endl;


    std::cout << "------------Task 5-----------" << std::endl;

    

    std::cout << "------------Task 6-----------" << std::endl;
    Hash_map<std::string, std::string, 1> table;

    table.insert("A", "B");
    table.insert("C", "B");
    table.insert("D", "E");
    table.insert("B", "E");
    table.insert("E", "E");
    table.insert("F", "A");

    Hash_map<std::string, int, 1> count_table;
    subordinates(table, count_table);
    count_table.display();

    return 0;
}