#pragma once

#include "GameMessage.h"


class RadiusChange : public GameMessage
{
public:
	RadiusChange(const float var);
	~RadiusChange();

	void process();

private:
	float mVar;
};