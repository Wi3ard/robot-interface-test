#pragma once

namespace robotsdk
{

class IRobot
{
public:
	virtual ~IRobot() = default;

	//
	// Public interface.
	//
public:
	virtual void Beep() = 0;
	virtual void Move(double distance) = 0;
	virtual void Turn(double angle) = 0;
};

}	// namespace robotsdk
