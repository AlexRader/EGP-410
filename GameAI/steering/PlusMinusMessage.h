#pragma once


#include "GameMessage.h"


class PlusMinusMessage : public GameMessage
{
public:
	PlusMinusMessage(const float var);
	~PlusMinusMessage();

	void process();

private:
	float mVar;
};