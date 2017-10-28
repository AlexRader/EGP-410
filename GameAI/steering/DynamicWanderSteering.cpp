#include "DynamicWanderSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
#include <cmath>

DynamicWanderSteering::DynamicWanderSteering(KinematicUnit *pMover)
	:mpMover(pMover)
{
	setWeight(0.1f);
	mApplyDirectly = false;
}

void DynamicWanderSteering::setAngle(Vector2D vec, float numb)
{
	float length = vec.getLength();
	vec.setX(cos(numb) * length);
	vec.setY(sin(numb) * length);

}

Steering* DynamicWanderSteering::getSteering()
{
	Vector2D circleCenter;
	circleCenter = mpMover->getVelocity();
	circleCenter.normalize();
	circleCenter *= CIRCLE_DISTANCE;
	Vector2D displacement;
	displacement = Vector2D(0.0f, genRandomBinomial());
	displacement *= CIRCLE_RADIUS;
	setAngle(displacement, mWanderAngle);
	mWanderAngle += (rand() * MAX_WANDERING_ROTATION) - (MAX_WANDERING_ROTATION * .5);

	Vector2D wanderForce;
	wanderForce = circleCenter + displacement;

	mLinear = wanderForce;
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mLinear.normalize();
	mLinear *= mpMover->getMaxAcceleration();
	mAngular = 0;

	return this;
}