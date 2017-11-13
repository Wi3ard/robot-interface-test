#pragma once

//! IRobot implementation for test.

class RobotMock
	: public robotsdk::IRobot
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	RobotMock()
		: angle_(0)
		, beepCount_(0)
		, distance_(0)
	{
	}
	// Delete implicit copy constructor and assignment operator.
	RobotMock(const RobotMock&) = delete;
	RobotMock& operator= (const RobotMock&) = delete;

	//
	// Public interface.
	//
public:
	void Beep() override final
	{
		++beepCount_;
	}
	double GetAngle() const
	{
		return angle_;
	}
	int GetBeepCount() const
	{
		return beepCount_;
	}
	double GetDistance() const
	{
		return distance_;
	}
	void Move(double distance) override final
	{
		distance_ += distance;
	}
	void Turn(double angle) override final
	{
		angle_ += angle;
	}

	//
	// Private data members.
	//
private:
	double angle_;
	int beepCount_;
	double distance_;
};
