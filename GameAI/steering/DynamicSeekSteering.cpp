#include "DynamicSeekSteering.h"
#include "KinematicUnit.h"
#include "Game.h"
DynamicSeekSteering::DynamicSeekSteering(KinematicUnit *pMover, KinematicUnit* pTarget, bool shouldFlee)
:mpMover(pMover)
,mpTarget(pTarget)
,mShouldFlee(shouldFlee)
{
	setWeight(1.2f);
	mApplyDirectly = false;
}

Steering* DynamicSeekSteering::getSteering()
{
	if( !mShouldFlee )
	{
		mLinear = mpTarget->getPosition() - mpMover->getPosition();
	}
	else
	{
		mLinear = mpMover->getPosition() - mpTarget->getPosition();
	}

	if (mLinear.getLength() > gpGame->getUnitManager()->getRadius())
		mLinear *= 0;

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;
	return this;
}