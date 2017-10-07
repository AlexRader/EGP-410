#include "KinematicWanderSteering.h"
#include "KinematicUnit.h"
#include "Game.h"


KinematicWanderSteering::KinematicWanderSteering(KinematicUnit* pMover, const Vector2D& targetPosition)
	:mpMover(pMover)
	,mTarget(targetPosition)
{
	mApplyDirectly = false;
}

Steering* KinematicWanderSteering::getSteering()
{
	mLinear = mTarget - mpMover->getPosition();
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;
	return this;
}