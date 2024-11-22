#include <gtest/gtest.h>
#include "CB_tree.hpp"   // Убедитесь, что этот заголовок определяет класс CBTree

class CBTreeTest : public ::testing::Test {
protected:
    CBTree tree;

    void SetUp() override {
        tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);
    }
};

TEST_F(CBTreeTest, InsertAndDisplay) {
    // Проверяем, что дерево не пустое после вставки
    EXPECT_TRUE(tree.get_value(1));
    EXPECT_TRUE(tree.get_value(2));
    EXPECT_TRUE(tree.get_value(3));
    EXPECT_TRUE(tree.get_value(4));
    EXPECT_TRUE(tree.get_value(5));
}

TEST_F(CBTreeTest, IsCBTTrue) {
    // Проверяем, что дерево является полным бинарным деревом
    EXPECT_TRUE(tree.is_CBT());
}

TEST_F(CBTreeTest, FindValueTrue) {
    // Проверяем, что поиск существующих значений работает
    EXPECT_TRUE(tree.get_value(3));
    EXPECT_TRUE(tree.get_value(4));
}

TEST_F(CBTreeTest, FindValueFalse) {
    // Проверяем, что поиск несуществующих значений работает
    EXPECT_FALSE(tree.get_value(6));
    EXPECT_FALSE(tree.get_value(7));
}

TEST_F(CBTreeTest, FindIndexValid) {
    // Проверяем, что поиск по индексу возвращает правильные значения
    testing::internal::CaptureStdout(); // захватываем вывод
    tree.find_index(0); // Ожидаем 1
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Value: 1\n");

    testing::internal::CaptureStdout();
    tree.find_index(2); // Ожидаем 3
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Value: 3\n");
}

TEST_F(CBTreeTest, FindIndexInvalid) {
    // Проверяем, что поиск по невалидному индексу работает
    testing::internal::CaptureStdout();
    tree.find_index(-1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Invalid index.\n");

    testing::internal::CaptureStdout();
    tree.find_index(10); // Индекс больше количества узлов
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Value not found.\n");
}

class CBTreeEmptyTest : public ::testing::Test {
protected:
    CBTree tree; // Создаем пустое дерево
};

TEST_F(CBTreeEmptyTest, GetValueOnEmptyTree) {
    testing::internal::CaptureStdout();
    EXPECT_FALSE(tree.get_value(1));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Tree is empty.\n");
}

TEST_F(CBTreeEmptyTest, FindIndexOnEmptyTree) {
    testing::internal::CaptureStdout();
    tree.find_index(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Tree is empty.\n");

    testing::internal::CaptureStdout();
    tree.find_index(-1);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Invalid index.\n");
}

class CBTreeDisplayTest : public ::testing::Test {
protected:
    CBTree tree;

    std::string captureDisplayOutput() {
        std::ostringstream buffer;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf()); // Перенаправляем cout

        tree.display(); // Вызываем метод display

        std::cout.rdbuf(oldCoutBuffer); // Восстанавливаем cout
        return buffer.str(); // Возвращаем захваченный вывод
    }
};

TEST_F(CBTreeDisplayTest, DisplayOnEmptyTree) {
    std::string output = captureDisplayOutput();
    EXPECT_EQ(output, "Tree is empty.\n");
}

TEST_F(CBTreeDisplayTest, DisplaySingleNodeTree) {
    tree.insert(1);

    std::string output = captureDisplayOutput();
    EXPECT_EQ(output, "1\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}