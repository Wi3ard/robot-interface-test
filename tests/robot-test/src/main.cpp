#include "pch.h"
#include "MockRobot.h"
#include "RobotCommand.h"

TEST(RobotTest, TestCommand)
{
	MockRobot robot1;

	auto beepCommand = MakeRobotCommand(&robotsdk::IRobot::Beep);
	auto moveCommand = MakeRobotCommand(&robotsdk::IRobot::Move, 0.05);
	auto turnCommand = MakeRobotCommand(&robotsdk::IRobot::Turn, 15.0);

	REQUIRE_CALL(robot1, Beep());
	REQUIRE_CALL(robot1, Move(0.05));
	REQUIRE_CALL(robot1, Turn(15.0));
	beepCommand->Execute(robot1);
	moveCommand->Execute(robot1);
	turnCommand->Execute(robot1);

	MockRobot robot2;
	REQUIRE_CALL(robot2, Beep())
		.TIMES(2);
	REQUIRE_CALL(robot2, Move(0.05))
		.TIMES(2);
	REQUIRE_CALL(robot2, Turn(15.0))
		.TIMES(2);
	beepCommand->Execute(robot2);
	beepCommand->Execute(robot2);
	moveCommand->Execute(robot2);
	moveCommand->Execute(robot2);
	turnCommand->Execute(robot2);
	turnCommand->Execute(robot2);

	MockRobot robot3;
	REQUIRE_CALL(robot3, Beep())
		.TIMES(10);
	REQUIRE_CALL(robot3, Move(0.05))
		.TIMES(10);
	REQUIRE_CALL(robot3, Turn(15.0))
		.TIMES(10);
	for (int n = 0; n < 10; ++n) {
		beepCommand->Execute(robot3);
		moveCommand->Execute(robot3);
		turnCommand->Execute(robot3);
	}
}

TEST(RobotTest, TestCommandSequence)
{
	MockRobot robot;

	trompeloeil::sequence seq;
	REQUIRE_CALL(robot, Move(0.19))
		.IN_SEQUENCE(seq);
	REQUIRE_CALL(robot, Turn(1.25))
		.IN_SEQUENCE(seq);
	REQUIRE_CALL(robot, Turn(0.12))
		.IN_SEQUENCE(seq);
	REQUIRE_CALL(robot, Beep())
		.IN_SEQUENCE(seq);
	REQUIRE_CALL(robot, Move(1.88))
		.IN_SEQUENCE(seq);
	REQUIRE_CALL(robot, Move(0.02))
		.IN_SEQUENCE(seq);
	REQUIRE_CALL(robot, Move(-1.29))
		.IN_SEQUENCE(seq);
	REQUIRE_CALL(robot, Turn(2.026))
		.IN_SEQUENCE(seq);
	REQUIRE_CALL(robot, Beep())
		.IN_SEQUENCE(seq);
	REQUIRE_CALL(robot, Beep())
		.IN_SEQUENCE(seq);

	std::vector<std::shared_ptr<IRobotCommand>> sequence;
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Move, 0.19));
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Turn, 1.25));
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Turn, 0.12));
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Beep));
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Move, 1.88));
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Move, 0.02));
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Move, -1.29));
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Turn, 2.026));
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Beep));
	sequence.emplace_back(MakeRobotCommand(&robotsdk::IRobot::Beep));

	for (const auto& command : sequence) {
		command->Execute(robot);
	}
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);

	// Set reporter for trompeloeil mocking framework.
	trompeloeil::set_reporter([](trompeloeil::severity s, const char* file, unsigned long line, const std::string& msg)
	{
		if (s == trompeloeil::severity::fatal)
		{
			std::ostringstream os;
			if (line != 0U) {
				os << file << ':' << line << '\n';
			}
			throw trompeloeil::expectation_violation(os.str() + msg);
		}

		ADD_FAILURE_AT(file, line) << msg;
	});

	// Run tests.
	auto result = RUN_ALL_TESTS();
}
