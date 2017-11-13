#pragma once

#include "Command.h"

//! Command specialization for IRobot interface.
typedef ICommand<robotsdk::IRobot> IRobotCommand;

template <typename Method, typename... Args>
std::shared_ptr<IRobotCommand> MakeRobotCommand(Method method, Args&&... args)
{
	return MakeCommand<robotsdk::IRobot>(method, std::forward<Args>(args)...);
}
