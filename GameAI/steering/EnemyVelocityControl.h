#pragma once

#include "GameMessage.h"


class EnemyVelocityControl : public GameMessage
{
public:
	EnemyVelocityControl(const float var);
	~EnemyVelocityControl();

	void process();

private:
	float mVar;
};