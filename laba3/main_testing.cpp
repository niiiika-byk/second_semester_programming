#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

#include "Array.hpp"
#include "List.hpp"
#include "Node.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "HashTable.hpp"
#include "CB_tree.hpp"

using namespace std;

TEST(ArrayTest, PushBack) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    EXPECT_EQ(arr.get_size(), 3);
}

TEST(ArrayTest, PushFront) {
    Array<int> arr;
    arr.push_front(1);
    arr.push_front(2);
    arr.push_front(3);
    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_TRUE(arr.search_index(0));  // Проверяем, что индекс 0 существует
    EXPECT_EQ(arr.get_value_at(0), 3);  // Проверяем, что на индексе 0 стоит 3
}

TEST(ArrayTest, PushIn) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(3);
    arr.push_in(1, 2);  // Вставляем 2 на индекс 1
    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr.get_value_at(1), 2);  // Проверяем, что на индексе 1 стоит 2
}

TEST(ArrayTest, PopFront) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.pop_front();
    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_EQ(arr.get_value_at(0), 2);  // Проверяем, что остался только 2
}

TEST(ArrayTest, PopBack) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.pop_back();
    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_EQ(arr.search_index(0), 1);  // Проверяем, что остался только 1
}

TEST(ArrayTest, PopIn) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.pop_in(1);  // Удаляем элемент по индексу 1
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr.get_value_at(1), 3);  // Проверяем, что на индексе 1 стоит 3
}

TEST(ArrayTest, Search) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    EXPECT_TRUE(arr.search(2));
    EXPECT_FALSE(arr.search(4));
}

TEST(ArrayTest, SetValueAt) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.set_value_at(1, 3);  // Устанавливаем значение 3 на индекс 1
    EXPECT_EQ(arr.get_value_at(1), 3);  // Проверяем, что на индексе 1 стоит 3
}

TEST(ArrayTest, InvalidIndexPopIn) {
    Array<int> arr;
    arr.push_back(1);
    arr.pop_in(5);  // Пытаемся удалить по несуществующему индексу
    EXPECT_EQ(arr.get_size(), 1);  // Размер должен остаться прежним
}

TEST(ArrayTest, InvalidIndexSetValueAt) {
    Array<int> arr;
    arr.push_back(1);
    arr.set_value_at(5, 10);  // Пытаемся установить значение по несуществующему индексу
    EXPECT_EQ(arr.search_index(0), 1);  // Проверяем, что первый элемент остался прежним
}

TEST(ArrayTest, PopFrontEmpty) {
    Array<int> arr;
    arr.pop_front();  // Пытаемся удалить из пустого массива
    EXPECT_EQ(arr.get_size(), 0);  // Размер должен оставаться 0
}

TEST(ArrayTest, PopBackEmpty) {
    Array<int> arr;
    arr.pop_back();  // Пытаемся удалить из пустого массива
    EXPECT_EQ(arr.get_size(), 0);  // Размер должен оставаться 0
}

TEST(ArrayTest, SearchIndexInvalidIndex) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    bool result = arr.search_index(5);  // Индекс 5 не существует
    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_TRUE(output.str().find("Invalid index") != std::string::npos);
    EXPECT_FALSE(result);
}

TEST(ArrayTest, SetValueAtInvalidIndex) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());
    arr.set_value_at(5, 10);  // Индекс 5 не существует

    std::cout.rdbuf(oldCoutBuffer);
    EXPECT_TRUE(output.str().find("Invalid index") != std::string::npos);
}

TEST(ArrayTest, GetValueAtInvalidIndex) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    EXPECT_THROW({
        arr.get_value_at(5);  // Индекс 5 не существует
    }, std::out_of_range);

    std::cout.rdbuf(oldCoutBuffer);
    EXPECT_TRUE(output.str().find("Invalid index") != std::string::npos);
}

TEST(ArrayTest, DisplayEmpty) {
    Array<int> arr;
    testing::internal::CaptureStdout();  // Захватываем стандартный вывод
    arr.display();  // Выводим массив
    std::string output = testing::internal::GetCapturedStdout();  // Получаем захваченный вывод
    EXPECT_EQ(output, "Array is empty.\n");  // Проверяем, что вывод соответствует ожидаемому
}

TEST(ArrayTest, DisplayNonEmpty) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    testing::internal::CaptureStdout();  // Захватываем стандартный вывод
    arr.display();  // Выводим массив
    std::string output = testing::internal::GetCapturedStdout();  // Получаем захваченный вывод
    EXPECT_EQ(output, "1 2 3 \n");  // Проверяем, что вывод соответствует ожидаемому
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// int main(){

//     std::cout << "--------------ARRAY-------------" << std::endl;
//     Array<int> arr;

//     arr.push_back(1); // Добавление в конец
//     arr.push_back(2);
//     arr.push_back(3);
//     arr.display();

//     arr.push_front(8);
//     arr.push_front(9);//добавление в начало
//     arr.display();

//     arr.search(1);
//     arr.search(17);

//     arr.push_in(1, 15); // Вставка по индексу
//     arr.display(); // Вывод

//     arr.pop_in(2); // Удаляем элемент 2
//     arr.display();

//     arr.pop_back();//удаляем последний
//     arr.display();

//     arr.pop_front();//удаляем первый
//     arr.display();

//     arr.search(15); // Поиск
//     arr.search( 50);

//     arr.display();

//     std::cout << "-------------LINKED LIST-------------" << std::endl;
//     LinkedList<string> list;
//     list.push_back("1");
//     list.push_front("2");
//     list.push_back("3");
//     list.push_back("4");
//     list.insert(3, "5");
//     list.display();//заполнение списка значениями

//     list.push_front("7");//вставка в начало

//     list.search("3");//поиск по значению
//     list.pop_value("4");

//     list.display();
//     list.pop_head();//удавление первого
//     list.display();
//     list.pop_tail();//удаление последнего
//     list.display();
//     list.pop(1);//удаление по индексу
//     list.display();

//     std::cout << "-------------DOUBLY LINKED LIST-------------" << std::endl;
//     DoublyList<int> doublyList;
//     doublyList.push_back(1);
//     doublyList.push_back(2);
//     doublyList.push_back(3);
//     doublyList.push_in(1, 8);
//     doublyList.push_back(4);
//     doublyList.push_front(9);//заполнение двусвязного списка
//     doublyList.display();

//     doublyList.search(4);//поиск по значению
//     doublyList.search(15);

//     doublyList.pop_forward();//удалить первый
//     doublyList.display();

//     doublyList.pop_backward();//удалить последний
//     doublyList.display();


//     doublyList.pop(2);
//     doublyList.pop_value(3);//удалить
//     doublyList.display();

//     std::cout << "-------------QUEUE-------------" << std::endl;
//     Queue<string> dq;
//     dq.push("5");
//     dq.push("4");
//     dq.push("3");
//     dq.push("2");
//     dq.push("1");//заполнение очереди
//     dq.display();

//     dq.search("5");//поиск по значению
//     dq.search("8");

//     dq.pop();//удаление
//     dq.pop();
//     dq.display();

//     std::cout << "-------------STACK-------------" << std::endl;
//     Stack<int> st;
//     st.push(5);
//     st.push(4);
//     st.push(3);
//     st.push(2);
//     st.push(1);//заполнение стека
//     st.display();

//     st.search(1);//поиск в стеке по значению
//     st.search(0);

//     st.pop();//последним пришел - первым выйдешь
//     st.display();

//     std::cout << "-------------HASH TABLE-------------" << std::endl;
//     Hash_map<int, std::string, 10> table;
//     table.insert(1, "one");
//     table.insert(2, "two");
//     table.insert(3, "three");//заполнение

//     std::string value = table.get_value(3);
//     if (value == "three") {
//         std::cout << "Value for key 3: " << value << std::endl;
//     } else {
//         std::cout << "Key 3 not found" << std::endl;
//     }

//     table.remove(2);

//     value = table.get_value(2);
//     if (value == "two") {
//         std::cout << "Value for key 2: " << value << std::endl;
//     } else {
//         std::cout << "Key 2 not found" << std::endl;
//     }

//     table.insert(1, "new one");

//     value = table.get_value(1);
//     if (value == "new one") {
//         std::cout << "Value for key 1: " << value << std::endl;
//     } else {
//         std::cout << "Key 1 not found" << std::endl;
//     }

//     std::cout << "--------------COMPLETE BINARY TREE-------------" << std::endl;

//     CBTree tree;
//     tree.insert(5);
//     tree.insert(15);
//     tree.insert(3);
//     tree.insert(7);
//     tree.insert(20);

//     std::cout << "Дерево:" << std::endl;
//     tree.display();
//     std::cout << std::endl;

//     if(tree.get_value(15)){
//         cout << "Value found" << endl;
//     }
//     else{
//         cout << "Value not found" << endl;
//     }

//     tree.find_index(3);

//     if (tree.is_CBT()){
//         cout << "Tree is CBT" << endl;
//     }
//     else {
//         cout << "Tree is not CBT" << endl;
//     }
    
//     return 0;
// }