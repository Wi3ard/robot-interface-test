#include "pch.h"

TEST(RobotTest, TestWorks)
{
	EXPECT_EQ(1, 1);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	auto result = RUN_ALL_TESTS();
}
