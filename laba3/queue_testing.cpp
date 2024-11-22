#include <gtest/gtest.h>
#include "Queue.hpp"

class QueueTest : public ::testing::Test {
protected:
    Queue<int> queue;

    void SetUp() override {
        // Опционально: установка начальных условий для тестов
    }
};

TEST_F(QueueTest, PushAndDisplay) {
    queue.push(1);
    queue.push(2);
    queue.push(3);
    
    testing::internal::CaptureStdout();
    queue.display();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "1 2 3 \n");
}

TEST_F(QueueTest, Pop) {
    queue.push(1);
    queue.push(2);
    queue.pop();
    
    testing::internal::CaptureStdout();
    queue.display();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "2 \n");
}

TEST_F(QueueTest, PopEmptyQueue) {
    testing::internal::CaptureStdout();
    queue.pop();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "Queue is empty!\n");
}

TEST_F(QueueTest, PopUntilEmpty) {
    queue.push(1);
    queue.push(2);
    queue.pop();
    queue.pop();
    
    testing::internal::CaptureStdout();
    queue.pop();  // Должен напечатать "Queue is empty!"
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "Queue is empty!\n");
}

TEST_F(QueueTest, SearchFound) {
    queue.push(1);
    queue.push(2);
    
    testing::internal::CaptureStdout();
    queue.search(2);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "Found!\n");
}

TEST_F(QueueTest, SearchNotFound) {
    queue.push(1);
    queue.push(2);
    
    testing::internal::CaptureStdout();
    queue.search(3);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "Not found!\n");
}

TEST_F(QueueTest, DisplayEmptyQueue) {
    testing::internal::CaptureStdout();
    queue.display();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "Queue is empty!\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}