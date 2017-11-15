#pragma once

class MockRobot
	: public robotsdk::IRobot
{
public:
	MAKE_MOCK0(Beep, void(), override);
	MAKE_MOCK1(Move, void(double), override);
	MAKE_MOCK1(Turn, void(double), override);
};
