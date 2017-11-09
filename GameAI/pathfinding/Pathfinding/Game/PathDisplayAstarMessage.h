#pragma once

#include "GameMessage.h"
#include <string>

class PathDisplayAstarMessage :public GameMessage
{
public:
	PathDisplayAstarMessage(const std::string path);
	~PathDisplayAstarMessage();

	void process();

private:
	std::string mPathType;
};