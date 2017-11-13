#pragma once

#include <robot-sdk/IRobot.h>

namespace robotsdk
{

class Robot
	: public IRobot
{
	//
	// Construction and destruction.
	//
public:
	// Delete implicit copy constructor and assignment operator.
	Robot(const Robot&) = delete;
	Robot& operator= (const Robot&) = delete;

	//
	// Public interface.
	//
public:
	void Move(double distance) override;
	void Turn(double angle) override;
	void Beep() override;
};

}	// namespace robotsdk
