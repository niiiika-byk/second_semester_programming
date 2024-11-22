#include <gtest/gtest.h>
#include "Array.hpp"

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