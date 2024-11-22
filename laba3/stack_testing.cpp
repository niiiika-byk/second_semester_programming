#include <gtest/gtest.h>
#include "Stack.hpp"  // Include your Stack implementation

class StackTest : public ::testing::Test {
protected:
    Stack<int> intStack;

    void SetUp() override {
        //
    }
};

TEST_F(StackTest, PushAndTop) {
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    
    EXPECT_EQ(intStack.top(), 3);
}

TEST_F(StackTest, Pop) {
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    
    intStack.pop();
    EXPECT_EQ(intStack.top(), 2);
}

TEST_F(StackTest, PopEmptyStack) {
    testing::internal::CaptureStdout();
    intStack.pop();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Stack is empty!\n");
}

TEST_F(StackTest, SearchFound) {
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    
    testing::internal::CaptureStdout();
    intStack.search(2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Found!\n");
}

TEST_F(StackTest, SearchNotFound) {
    intStack.push(1);
    intStack.push(2);
    
    testing::internal::CaptureStdout();
    intStack.search(3);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Not found!\n");
}

TEST_F(StackTest, IsEmpty) {
    EXPECT_TRUE(intStack.isEmpty());
    intStack.push(1);
    EXPECT_FALSE(intStack.isEmpty());
}

TEST_F(StackTest, TopEmphy) {
    testing::internal::CaptureStdout();
    intStack.top();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Stack is empty!\n");
}

TEST_F(StackTest, DisplayStack) {
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    testing::internal::CaptureStdout();
    intStack.display();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "3 2 1 \n");
}

TEST_F(StackTest, DisplayEmptyStack) {
    testing::internal::CaptureStdout();
    intStack.display();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}