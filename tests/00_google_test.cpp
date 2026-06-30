#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <iostream>

TEST(GoogleTestExamples, EXPECT_EQ) {
    const int a = 10;
    const int b = 10;
    EXPECT_EQ(a, b);
}

TEST(GoogleTestExamples, EXPECT_NE) {
    const int a = 10;
    const int b = 11;
    EXPECT_NE(a, b);
}

TEST(GoogleTestExamples, EXPECT_FLOAT_EQ) {
    const float a = 10.0f;
    const float b = 10.000001f;
    EXPECT_FLOAT_EQ(a, b);
}

TEST(GoogleTestExamples, EXPECT_DOUBLE_EQ) {
    const double a = 10.0;
    const double b = 10.0;
    EXPECT_DOUBLE_EQ(a, b);
}

TEST(GoogleTestExamples, ArrayException) {
    constexpr std::array<int, 3> my_array = {1,2,3};
    EXPECT_THROW((void)my_array.at(10), std::out_of_range);
}

TEST(GoogleTestExamples, CaputreOStream) {
    testing::internal::CaptureStdout();

    std::cout << "Hello World";

    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello World");
}

class TestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        speed = 100;
    }

    int speed{};
};

TEST_F(TestFixture, IncreasesSpeed) {
    speed += 50;
    EXPECT_EQ(speed, 150);
}

TEST_F(TestFixture, DecreasesSpeed) {
    speed -= 30;
    EXPECT_EQ(speed, 70);
}
class AbsTest : public ::testing::TestWithParam<std::pair<int, int>> {
    // no setup needed
};

TEST_P(AbsTest, ComputesAbsoluteValue) {
    int input = GetParam().first;
    int expected = GetParam().second;

    EXPECT_EQ(std::abs(input), expected);
}

INSTANTIATE_TEST_SUITE_P(
    AbsValues,
    AbsTest,
    ::testing::Values(
        std::make_pair(-3, 3),
        std::make_pair(-1, 1),
        std::make_pair(0, 0),
        std::make_pair(2, 2)
    )
);

// GMock Tests
TEST(TestRandowmNumbers, RandomInt)
{
    std::string output = "Hello";
    ASSERT_THAT(output, testing::Not(testing::IsEmpty()));
}