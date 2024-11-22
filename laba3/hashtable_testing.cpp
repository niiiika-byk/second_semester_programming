#include <gtest/gtest.h>
#include "HashTable.hpp"

class HashMapTest : public ::testing::Test {
protected:
    Hash_map<int, std::string, 10> hash_map;

    void SetUp() override {
        //
    }
};

TEST_F(HashMapTest, InsertAndGet) {
    hash_map.insert(1, "One");
    hash_map.insert(2, "Two");
    hash_map.insert(3, "Three");

    EXPECT_EQ(hash_map.get_value(1), "One");
    EXPECT_EQ(hash_map.get_value(2), "Two");
    EXPECT_EQ(hash_map.get_value(3), "Three");
}

TEST_F(HashMapTest, GetNonExistentKey) {
    EXPECT_EQ(hash_map.get_value(99), std::string());
}

TEST_F(HashMapTest, InsertDuplicateKey) {
    hash_map.insert(1, "One");
    hash_map.insert(1, "Uno");

    EXPECT_EQ(hash_map.get_value(1), "Uno");
}

TEST_F(HashMapTest, RemoveKey) {
    hash_map.insert(1, "One");
    hash_map.remove(1);
    
    EXPECT_EQ(hash_map.get_value(1), std::string());
}

TEST_F(HashMapTest, RemoveNonExistentKey) {
    hash_map.insert(1, "One");
    hash_map.remove(2); // Удаляем несуществующий ключ
    EXPECT_EQ(hash_map.get_value(1), "One"); // Значение должно остаться
}

TEST_F(HashMapTest, Display) {
    testing::internal::CaptureStdout();
    hash_map.insert(1, "One");
    hash_map.insert(2, "Two");
    hash_map.insert(3, "Three");
    hash_map.display();
    
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Key: 1, Value: One") != std::string::npos);
    EXPECT_TRUE(output.find("Key: 2, Value: Two") != std::string::npos);
    EXPECT_TRUE(output.find("Key: 3, Value: Three") != std::string::npos);
}

class HashMapCollisionTest : public ::testing::Test {
protected:
    Hash_map<int, std::string, 10> hash_map;

    void SetUp() override {
        // Вставляем элементы с одинаковым хэш-значением
        hash_map.insert(1, "One");
        hash_map.insert(11, "Eleven"); // Предполагается, что хэш-функция для 11 дает такой же индекс, как и для 1
        hash_map.insert(21, "Twenty-One"); // То же самое для 21
    }
};

TEST_F(HashMapCollisionTest, GetValueWithCollision) {
    EXPECT_EQ(hash_map.get_value(1), "One");
    EXPECT_EQ(hash_map.get_value(11), "Eleven");
    EXPECT_EQ(hash_map.get_value(21), "Twenty-One");
}

TEST_F(HashMapCollisionTest, GetNonExistentKey) {
    EXPECT_EQ(hash_map.get_value(2), std::string()); // Не существует
}

TEST_F(HashMapCollisionTest, RemoveMiddleElement) {
    hash_map.remove(11); // Удаляем элемент с ключом 11

    // Проверяем, что элемент с ключом 11 был удален
    EXPECT_EQ(hash_map.get_value(11), std::string());
    
    // Проверяем, что другие элементы остались
    EXPECT_EQ(hash_map.get_value(1), "One");
    EXPECT_EQ(hash_map.get_value(21), "Twenty-One");
}

TEST_F(HashMapCollisionTest, RemoveHeadElement) {
    hash_map.remove(1); // Удаляем элемент с ключом 1

    // Проверяем, что элемент с ключом 1 был удален
    EXPECT_EQ(hash_map.get_value(1), std::string());

    // Проверяем, что другие элементы остались
    EXPECT_EQ(hash_map.get_value(11), "Eleven");
    EXPECT_EQ(hash_map.get_value(21), "Twenty-One");
}

TEST_F(HashMapCollisionTest, RemoveTailElement) {
    hash_map.remove(21); // Удаляем элемент с ключом 21

    // Проверяем, что элемент с ключом 21 был удален
    EXPECT_EQ(hash_map.get_value(21), std::string());

    // Проверяем, что другие элементы остались
    EXPECT_EQ(hash_map.get_value(1), "One");
    EXPECT_EQ(hash_map.get_value(11), "Eleven");
}

TEST_F(HashMapCollisionTest, RemoveNonExistentElement) {
    hash_map.remove(99); // Удаляем несуществующий элемент

    // Проверяем, что другие элементы остались
    EXPECT_EQ(hash_map.get_value(1), "One");
    EXPECT_EQ(hash_map.get_value(11), "Eleven");
    EXPECT_EQ(hash_map.get_value(21), "Twenty-One");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}