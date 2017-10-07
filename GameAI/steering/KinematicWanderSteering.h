#pragma once

#include "Steering.h"

class KinematicUnit;

const float MAX_WANDER_ROTATION = 1.0f;

class KinematicWanderSteering:public Steering
{
public:
	KinematicWanderSteering(KinematicUnit* pMover, const Vector2D& targetPosition);
	~KinematicWanderSteering(){};

	virtual void setTarget(const Vector2D& targetPosition) { mTarget = targetPosition; };

	virtual Steering* getSteering();

private:
	Vector2D mTarget;
	KinematicUnit* mpMover;
};