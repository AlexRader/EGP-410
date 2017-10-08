#pragma once


#include "GameMessage.h"


class AngularControl : public GameMessage
{
public:
	AngularControl(const float var);
	~AngularControl();

	void process();

private:
	float mVar;
};