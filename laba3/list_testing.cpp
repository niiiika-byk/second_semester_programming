#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

#include "List.hpp"

using namespace std;

class LinkedListTest : public ::testing::Test {
protected:
    LinkedList<int> list;

    void SetUp() override {
        // Можно инициализировать список или что-то еще, если нужно
    }
};

TEST_F(LinkedListTest, PushFront) {
    list.push_front(10);
    list.push_front(20);
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "20 10 \n");
}

TEST_F(LinkedListTest, PushBack) {
    list.push_back(10);
    list.push_back(20);
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "10 20 \n");
}

TEST_F(LinkedListTest, InsertValidIndex) {
    list.insert(0, 1);
    list.push_back(10);
    list.push_back(30);
    list.insert(1, 20);
    list.insert(0, 40);
    list.insert(5, 50);
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "40 1 20 10 30 50 \n");
}

TEST_F(LinkedListTest, InsertInvalidIndex) {
    // Перенаправляем вывод в строковый поток
    testing::internal::CaptureStdout();

    list.insert(-1, 20);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Invalid index\n");

    // Очищаем поток вывода для следующей проверки
    testing::internal::CaptureStdout();

    list.push_back(10);
    list.insert(2, 30);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Invalid index\n");
}

TEST_F(LinkedListTest, PopHead) {
    list.push_back(10);
    list.push_back(20);
    list.pop_head();
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "20 \n");
}

TEST_F(LinkedListTest, PopHeadEmptyList) {
    std::ostringstream output;
    testing::internal::CaptureStdout();

    list.pop_head();
    
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "List is empty\n");
}

TEST_F(LinkedListTest, PopTail) {
    list.push_back(10);
    list.push_back(20);
    list.pop_tail();
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "10 \n");
}

TEST_F(LinkedListTest, PopTailEmptyList) {
    list.pop_tail();
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "List is empty\n");
}

TEST_F(LinkedListTest, PopTailSingleNode) {
    list.push_back(10);
    list.pop_tail();
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "List is empty\n");
}

TEST_F(LinkedListTest, PopInHead) {
    list.push_back(10);
    list.push_back(20);
    list.pop(0); // Удаляем элемент с индексом 0
    EXPECT_EQ(list.get_value(0), 20); // Проверяем, что остался элемент 20

    list.push_back(30);
    list.pop(1); // Удаляем элемент с индексом 1
    EXPECT_EQ(list.get_value(0), 20);

    testing::internal::CaptureStdout(); // Захватываем вывод
    list.pop(3);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Invalid index\n");
}

TEST_F(LinkedListTest, PopFromEmptyList) {
    testing::internal::CaptureStdout(); // Захватываем вывод
    list.pop(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "List is empty\n");
}

TEST_F(LinkedListTest, PopInvalidIndex) {
    testing::internal::CaptureStdout(); // Захватываем вывод
    list.pop(-1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Invalid index\n");
}

TEST_F(LinkedListTest, GetValueValidIndex) {
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_EQ(list.get_value(0), 10);  // Проверяем первый элемент
    EXPECT_EQ(list.get_value(1), 20);  // Проверяем второй элемент
    EXPECT_EQ(list.get_value(2), 30);  // Проверяем третий элемент
}

TEST_F(LinkedListTest, GetValueInvalidIndexMax) {
    list.push_back(10);
    EXPECT_THROW(list.get_value(1), std::out_of_range);   // Проверяем индекс, выходящий за пределы
}

TEST_F(LinkedListTest, GetValueInvalidIndex) {
    EXPECT_THROW(list.get_value(-1), std::out_of_range);
}

TEST_F(LinkedListTest, GetValueFromEmptyList) {
    LinkedList<int> emptyList;
    EXPECT_THROW(emptyList.get_value(0), std::out_of_range);  // Проверяем получение значения из пустого списка
}

TEST_F(LinkedListTest, SearchExistingElement) {
    list.push_back(20);
    testing::internal::CaptureStdout(); // Перенаправление вывода в строку
    list.search(20);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "yes!\n"); // Проверка, что вывод "yes!"
}

TEST_F(LinkedListTest, SearchNonExistingElement) {
    list.push_back(10);
    list.push_back(20);
    testing::internal::CaptureStdout(); // Перенаправление вывода в строку
    list.search(40);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "No element in list\n"); // Проверка, что вывод "No element in list"
}

TEST_F(LinkedListTest, SearchInEmptyList) {
    LinkedList<int> emptyList;
    testing::internal::CaptureStdout(); // Перенаправление вывода в строку
    emptyList.search(10);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "List is empty\n"); // Проверка, что вывод "No element in list"
}

TEST_F(LinkedListTest, DisplayEmptyList) {
    std::ostringstream output;
    testing::internal::CaptureStdout();  // Перенаправляем стандартный вывод

    list.display();

    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "List is empty\n");
}

TEST_F(LinkedListTest, PopValueHead) {
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_value(10);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "20 30 \n");
}

TEST_F(LinkedListTest, PopValueTail) {
    list.push_back(10);
    list.push_back(20);
    list.pop_value(20);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "10 \n");
}

TEST_F(LinkedListTest, PopValueInList) {
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.pop_value(20);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "10 30 \n");
}

TEST_F(LinkedListTest, PopValueFromEmptyList) {
    LinkedList<int> emptyList;
    testing::internal::CaptureStdout();
    emptyList.pop_value(10);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "List is empty\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}