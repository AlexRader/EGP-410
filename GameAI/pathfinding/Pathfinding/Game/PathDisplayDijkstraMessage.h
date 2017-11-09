#pragma once

#include "GameMessage.h"
#include <string>

class PathDisplayDijkstraMessage :public GameMessage
{
public:
	PathDisplayDijkstraMessage(const std::string path);
	~PathDisplayDijkstraMessage();

	void process();

private:
	std::string mPathType;
};