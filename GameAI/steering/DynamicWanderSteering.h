#pragma once


#include "Steering.h"

class KinematicUnit;

const float MAX_WANDERING_ROTATION = 0.5f;
const float CIRCLE_DISTANCE = 3.0f;
const float CIRCLE_RADIUS = 10.0f;

class DynamicWanderSteering :public Steering
{
public:
	DynamicWanderSteering(KinematicUnit* pMover);
	~DynamicWanderSteering() {};

	//void setTarget();
	void setAngle(Vector2D vec, float numb);
	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	float mWanderAngle = 15;
};