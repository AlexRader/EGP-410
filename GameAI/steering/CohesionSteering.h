#pragma once

#include "Steering.h"
#include "Game.h"

class KinematicUnit;

const float DECAY_COEFFICIENT_VARIENT = -20.0f;
const float ADDED_RANGE = 20.0f;

class CohesionSteering :public Steering
{
public:
	CohesionSteering(KinematicUnit* pMover);
	~CohesionSteering() {};

	virtual Steering* getSteering();

	//added this in just for collision avoidence
	float dot(Vector2D& v1, Vector2D& v2) { return v1.getX() * v2.getX() + v1.getY() * v2.getY(); };

private:
	KinematicUnit* mpMover;
	float mReaction, mDistance, mStrength;
	Vector2D mDirection;
};
