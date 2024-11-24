#include "Array.hpp"
#include "List.hpp"

int main() {
    //для массива
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    // Сериализация
    arr.serialize("array.bin");
    
    // Создаем новый массив и десериализуем в него данные
    Array<int> newArr;
    newArr.deserialize("array.bin");
    
    // Отображаем содержимое нового массива
    std::cout << "New array: ";
    newArr.display();
    

    //для листа
    LinkedList<int> list;
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);

    list.serialize("list.bin");
    LinkedList<int> newList;
    newList.deserialize("list.bin");

    std::cout << "New linked list: ";
    newList.display();


    //для двусвязного листа
    DoublyList<int> doublyList;
    doublyList.push_back(7);
    doublyList.push_back(8);
    doublyList.push_back(9);

    doublyList.serialize("doublyList.bin");
    DoublyList<int> newDoublyList;
    newDoublyList.deserialize("doublyList.bin");

    std::cout << "New doubly linked list: ";
    newDoublyList.display();

    return 0;
}