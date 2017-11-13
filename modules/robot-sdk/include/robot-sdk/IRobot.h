#pragma once

namespace robotsdk
{

class IRobot
{
public:
	virtual ~IRobot() {}

	//
	// Public interface.
	//
public:
	virtual void Move(double distance) = 0;
	virtual void Turn(double angle) = 0;
	virtual void Beep() = 0;
};

}	// namespace robotsdk