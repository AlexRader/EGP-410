#pragma once

#include "GameMessage.h"


class DisplayDebug : public GameMessage
{
public:
	DisplayDebug();
	~DisplayDebug();

	void process();

private:

};