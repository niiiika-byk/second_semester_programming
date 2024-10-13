#include <iostream>

//1
#include "expression.hpp"
//4
#include "Array.hpp"
//6
#include "hash_table.hpp"
#include "subordinates.hpp"

int main(){
    std::cout << "------------Task 1-----------" << std::endl;
    std::string expression = "1 & (0 | 1) ^ 1";
    std::cout << "Expression: " << expression << std::endl;
    
    int result = evaluate_expression(expression);
    std::cout << "Result: " << result << std::endl;

    std::cout << "------------Task 3-----------" << std::endl;


    std::cout << "------------Task 4-----------" << std::endl;
    Array<int> arr;
    arr.push_back(4);
    arr.push_back(-7);
    arr.push_back(1);
    arr.push_back(5);
    arr.push_back(-4);
    arr.push_back(0);
    arr.push_back(-3);
    arr.push_back(2);
    arr.push_back(4);
    arr.push_back(1);

    std::cout << "Array: ";
    arr.display();

    int target_sum = 5;
    std::cout << "Finding subarrays with sum " << target_sum << ":\n";
    arr.find_sum(target_sum);

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