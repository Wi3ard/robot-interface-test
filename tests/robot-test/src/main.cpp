#include "pch.h"
#include "RobotCommand.h"
#include "RobotMock.h"

TEST(RobotTest, TestCommand)
{
	RobotMock robot1;
	RobotMock robot2;
	RobotMock robot3;

	auto beepCommand = MakeRobotCommand(&robotsdk::IRobot::Beep);
	auto moveCommand = MakeRobotCommand(&robotsdk::IRobot::Move, 0.05);
	auto turnCommand = MakeRobotCommand(&robotsdk::IRobot::Turn, 15.0);

	beepCommand->Execute(robot1);
	EXPECT_EQ(robot1.GetBeepCount(), 1);
	moveCommand->Execute(robot1);
	EXPECT_DOUBLE_EQ(robot1.GetDistance(), 0.05);
	turnCommand->Execute(robot1);
	EXPECT_DOUBLE_EQ(robot1.GetAngle(), 15.0);

	beepCommand->Execute(robot2);
	beepCommand->Execute(robot2);
	EXPECT_EQ(robot2.GetBeepCount(), 2);
	moveCommand->Execute(robot2);
	moveCommand->Execute(robot2);
	EXPECT_DOUBLE_EQ(robot2.GetDistance(), 0.1);
	turnCommand->Execute(robot2);
	turnCommand->Execute(robot2);
	EXPECT_DOUBLE_EQ(robot2.GetAngle(), 30.0);

	for (int n = 0; n < 10; ++n) {
		beepCommand->Execute(robot3);
		moveCommand->Execute(robot3);
		turnCommand->Execute(robot3);
	}
	EXPECT_EQ(robot3.GetBeepCount(), 10);
	EXPECT_DOUBLE_EQ(robot3.GetDistance(), 0.5);
	EXPECT_DOUBLE_EQ(robot3.GetAngle(), 150.0);
}

TEST(RobotTest, TestCommandSequence)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.01, 100.0);
	
	std::vector<std::shared_ptr<IRobotCommand>> sequence;
	RobotMock robot1;

	int count = std::uniform_int_distribution<>(1, 100)(gen);
	for (int n = 0; n < count; ++n) {
		sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Beep));
		sequence.back()->Execute(robot1);
		sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Move, dis(gen)));
		sequence.back()->Execute(robot1);
		sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Turn, dis(gen)));
		sequence.back()->Execute(robot1);
	}

	// Replay the same sequence on another robot.
	RobotMock robot2;
	for (const auto& command : sequence) {
		command->Execute(robot2);
	}

	EXPECT_EQ(robot1.GetBeepCount(), robot2.GetBeepCount());
	EXPECT_DOUBLE_EQ(robot1.GetAngle(), robot2.GetAngle());
	EXPECT_DOUBLE_EQ(robot1.GetDistance(), robot2.GetDistance());
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	auto result = RUN_ALL_TESTS();
}
