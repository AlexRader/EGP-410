#pragma once
#include "GameMessage.h"

class RemoveAi :public GameMessage
{
public:
	RemoveAi();
	~RemoveAi();

	void process();
};