#include <gtest/gtest.h> // googletest header file

#include <string>
using std::string;

TEST(DEFAULT, CStrEqual) {
    EXPECT_STREQ("hello gtest", "hello gtest");
}

TEST(Default, CStrNotEqual) {
    EXPECT_STREQ("hello gtest2", "hello world");
}