#pragma once

#include "GameMessage.h"
#include <string>

class EscapeMessage :public GameMessage
{
public:
	EscapeMessage();
	~EscapeMessage();

	void process();

private:
};