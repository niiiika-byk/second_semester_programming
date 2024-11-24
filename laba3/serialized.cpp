#include "Array.hpp"
#include "List.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "HashTable.hpp"
#include "CB_tree.hpp"

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
    std::cout << "\tNew array: ";
    newArr.display();
    

    //для листа
    LinkedList<int> list;
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);

    list.serialize("list.bin");
    LinkedList<int> newList;
    newList.deserialize("list.bin");

    std::cout << "\tNew linked list: ";
    newList.display();


    //для двусвязного листа
    DoublyList<int> doublyList;
    doublyList.push_back(7);
    doublyList.push_back(8);
    doublyList.push_back(9);

    doublyList.serialize("doublyList.bin");
    DoublyList<int> newDoublyList;
    newDoublyList.deserialize("doublyList.bin");

    std::cout << "\tNew doubly linked list: ";
    newDoublyList.display();

    //очередь
    Queue<int> queue;
    queue.push(10);
    queue.push(11);
    queue.push(12);

    queue.serialize("queue.bin");
    Queue<int> newQueue;
    newQueue.deserialize("queue.bin");

    std::cout << "\tNew queue: ";
    newQueue.display();

    //стек
    Stack<int> stack;
    stack.push(13);
    stack.push(14);
    stack.push(15);

    stack.serialize("stack.bin");
    Stack<int> newStack;
    newStack.deserialize("stack.bin");

    std::cout << "\tNew stack: ";
    newStack.display();

    Hash_map<std::string, int, 1> hash_table;
    for (int i = 0; i < 3; i++) {
        hash_table.insert("key" + to_string(i), i + 1);  // Заполнение карты с ключами в виде строк
    }

    hash_table.serialize("hash_table.bin");
    Hash_map<std::string, int, 1> new_hash_table;
    new_hash_table.deserialize("hash_table.bin");

    std::cout << "\tNew hash table:\n";
    new_hash_table.display();

    //дерево
    CBTree cb_tree;
    cb_tree.insert(16);
    cb_tree.insert(17);
    cb_tree.insert(18);

    cb_tree.serialize("cb_tree.bin");
    CBTree new_cb_tree;
    new_cb_tree.deserialize("cb_tree.bin");

    std::cout << "\tNew CB tree:\n";
    new_cb_tree.display();

    return 0;
}