#include <iostream>
#include <string>
#include <sstream>

#include "Array.hpp"
#include "List.hpp"
#include "Node.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "HashTable.hpp"
#include "CB_tree.hpp"

using namespace std;

int main(){

    std::cout << "--------------ARRAY-------------" << std::endl;
    Array<int> arr;

    arr.push_back(1); // Добавление в конец
    arr.push_back(2);
    arr.push_back(3);
    arr.display();

    arr.push_front(8);
    arr.push_front(9);//добавление в начало
    arr.display();

    arr.search(1);
    arr.search(17);

    arr.push_in(1, 15); // Вставка по индексу
    arr.display(); // Вывод

    arr.pop_in(2); // Удаляем элемент 2
    arr.display();

    arr.pop_back();//удаляем последний
    arr.display();

    arr.pop_front();//удаляем первый
    arr.display();

    arr.search(15); // Поиск
    arr.search( 50);

    arr.display();

    std::cout << "-------------LINKED LIST-------------" << std::endl;
    LinkedList<string> list;
    list.push_back("1");
    list.push_front("2");
    list.push_back("3");
    list.push_back("4");
    list.insert(3, "5");
    list.display();//заполнение списка значениями

    list.push_front("7");//вставка в начало

    list.search("3");//поиск по значению
    list.pop_value("4");

    list.display();
    list.pop_head();//удавление первого
    list.display();
    list.pop_tail();//удаление последнего
    list.display();
    list.pop(1);//удаление по индексу
    list.display();

    std::cout << "-------------DOUBLY LINKED LIST-------------" << std::endl;
    DoublyList<int> doublyList;
    doublyList.push_back(1);
    doublyList.push_back(2);
    doublyList.push_back(3);
    doublyList.push_in(1, 8);
    doublyList.push_back(4);
    doublyList.push_front(9);//заполнение двусвязного списка
    doublyList.display();

    doublyList.search(4);//поиск по значению
    doublyList.search(15);

    doublyList.pop_forward();//удалить первый
    doublyList.display();

    doublyList.pop_backward();//удалить последний
    doublyList.display();


    doublyList.pop(2);
    doublyList.pop_value(3);//удалить
    doublyList.display();

    std::cout << "-------------QUEUE-------------" << std::endl;
    Queue<string> dq;
    dq.push("5");
    dq.push("4");
    dq.push("3");
    dq.push("2");
    dq.push("1");//заполнение очереди
    dq.display();

    dq.search("5");//поиск по значению
    dq.search("8");

    dq.pop();//удаление
    dq.pop();
    dq.display();

    std::cout << "-------------STACK-------------" << std::endl;
    Stack<int> st;
    st.push(5);
    st.push(4);
    st.push(3);
    st.push(2);
    st.push(1);//заполнение стека
    st.display();

    st.search(1);//поиск в стеке по значению
    st.search(0);

    st.pop();//последним пришел - первым выйдешь
    st.display();

    std::cout << "-------------HASH TABLE-------------" << std::endl;
    Hash_map<int, std::string, 10> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");//заполнение

    std::string value;
    if (table.get_value(3) == "three") {
        std::cout << "Value for key 3: " << value << std::endl;
    } else {
        std::cout << "Key 3 not found" << std::endl;
    }

    table.remove(2);

    if (table.get_value(2) == "two") {
        std::cout << "Value for key 2: " << value << std::endl;
    } else {
        std::cout << "Key 2 not found" << std::endl;
    }

    table.insert(1, "new one");

    if (table.get_value(1) == "new one") {
        std::cout << "Value for key 1: " << value << std::endl;
    } else {
        std::cout << "Key 1 not found" << std::endl;
    }

    std::cout << "--------------COMPLETE BINARY TREE-------------" << std::endl;

    CBTree tree;
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(20);

    std::cout << "Дерево:" << std::endl;
    tree.display();
    std::cout << std::endl;

    if(tree.get_value(15)){
        cout << "Value found" << endl;
    }
    else{
        cout << "Value not found" << endl;
    }

    tree.find_index(3);

    if (tree.is_CBT()){
        cout << "Tree is CBT" << endl;
    }
    else {
        cout << "Tree is not CBT" << endl;
    }
    
    return 0;
}