#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

#include "List.hpp"

using namespace std;

class DoublyListTest : public ::testing::Test {
protected:
    DoublyList<int> list;

    void SetUp() override {
        // Можно инициализировать список или что-то еще, если нужно
    }
};

TEST_F(DoublyListTest, PushFront) {
    list.push_front(10);
    list.push_front(20);
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "20 10 \n");
}

TEST_F(DoublyListTest, PushBack) {
    list.push_back(10);
    list.push_back(20);
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "10 20 \n");
}

TEST_F(DoublyListTest, InsertValidIndex) {
    list.push_in(0, 1);
    list.push_back(10);
    list.push_back(30);
    list.push_in(1, 20);
    list.push_in(0, 40);
    list.push_in(5, 50);
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "40 1 20 10 30 50 \n");
}

TEST_F(DoublyListTest, InsertInvalidIndex) {
    // Перенаправляем вывод в строковый поток
    testing::internal::CaptureStdout();

    list.push_in(-1, 20);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Invalid index\n");

    // Очищаем поток вывода для следующей проверки
    testing::internal::CaptureStdout();

    list.push_back(10);
    list.push_in(2, 30);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Index out of bounds\n");
}

TEST_F(DoublyListTest, SearchExistingElement) {
    list.push_back(20);
    testing::internal::CaptureStdout(); // Перенаправление вывода в строку
    list.search(20);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Yes!!\n"); // Проверка, что вывод "yes!"
}

TEST_F(DoublyListTest, SearchNonExistingElement) {
    list.push_back(10);
    list.push_back(20);
    testing::internal::CaptureStdout(); // Перенаправление вывода в строку
    list.search(40);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "No element\n"); // Проверка, что вывод "No element in list"
}

TEST_F(DoublyListTest, PopHead) {
    list.push_back(10);
    list.push_back(20);
    list.pop_forward();
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "20 \n");

    list.pop_forward();
}

TEST_F(DoublyListTest, PopTail) {
    list.push_back(10);
    list.push_back(20);
    list.pop_backward();
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.str(), "10 \n");

    list.pop_backward();
}

TEST_F(DoublyListTest, PopInHead) {
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

TEST_F(DoublyListTest, PopFromEmptyList) {
    testing::internal::CaptureStdout(); // Захватываем вывод
    list.pop(-1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Invalid index\n");
}

TEST_F(DoublyListTest, GetValueValidIndex) {
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_EQ(list.get_value(0), 10);  // Проверяем первый элемент
    EXPECT_EQ(list.get_value(1), 20);  // Проверяем второй элемент
    EXPECT_EQ(list.get_value(2), 30);  // Проверяем третий элемент
}

TEST_F(DoublyListTest, GetValueInvalidIndexMax) {
    list.push_back(10);
    EXPECT_THROW(list.get_value(1), std::out_of_range);   // Проверяем индекс, выходящий за пределы
}

TEST_F(DoublyListTest, GetValueInvalidIndex) {
    EXPECT_THROW(list.get_value(-1), std::out_of_range);
}

TEST_F(DoublyListTest, GetValueFromEmptyList) {
    LinkedList<int> emptyList;
    EXPECT_THROW(emptyList.get_value(0), std::out_of_range);  // Проверяем получение значения из пустого списка
}

TEST_F(DoublyListTest, PopValueHead) {
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

TEST_F(DoublyListTest, PopValueTail) {
    list.push_back(10);
    list.push_back(20);
    list.pop_value(20);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.display();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "10 \n");
}

TEST_F(DoublyListTest, PopValueInList) {
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

TEST_F(DoublyListTest, PopValueFromEmptyList) {
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