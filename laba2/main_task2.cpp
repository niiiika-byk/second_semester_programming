#include <iostream>
#include <string>
#include <sstream>

#include "set.hpp"

Set<int> mySet;

int main() {
    // Интерактивный ввод команд
    std::string query;
    std::cout << "Input the command ('EXIT'):" << std::endl;
    while (true) {
        std::cout << ">>> ";
        getline(std::cin, query);

        if (query == "EXIT") {
            break; // Выход из цикла
        }

        std::stringstream ss(query);
        std::string command;
        ss >> command;
        if (command == "SETADD"){ // Добавление элемента
            mySet.load_from_file("set.txt");
            int value;
            ss >> value;
            mySet.add(value);
            mySet.save_to_file("set.txt");
        }
        else if (command == "SETDEL"){ // Удаление элемента
            mySet.load_from_file("set.txt");
            int value;
            ss >> value;
            mySet.remove(value);
            mySet.save_to_file("set.txt");
        }
        else if (command == "SET_AT"){ // Получение значения по ключу
            int value;
            ss >> value;
            std::cout << "Is "<< value <<" a member: " << mySet.is_member(value) << std::endl;
        }
        else if (command == "SETPRINT"){ //Вывод на экран
            mySet.load_from_file("set.txt");
            mySet.display();
        }
        else {
            std::cout << "Invalid command" << std::endl;
        }
    }
    return 0;
}