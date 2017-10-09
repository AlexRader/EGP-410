#include "KinematicUnit.h"
#include "CollisionAvoidenceSteering.h"
#include <algorithm> 

CollisionAvoidenceSteering::CollisionAvoidenceSteering(KinematicUnit* pMover)
	:mpMover(pMover)
	,mReaction(64.0f)
{
	setWeight(1.0f);
}


Steering* CollisionAvoidenceSteering::getSteering()
{
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); ++i)
	{
		mDirection = gpGame->getUnitManager()->getUnit(i)->getPosition() - mpMover->getPosition();
		mDistance = mDirection.getLength();

		if (mDistance < mReaction && gpGame->getUnitManager()->getUnit(i) != mpMover)
		{
			mStrength = min(DECAY_COEFFICIENT / (mDistance * mDistance), gpGame->getUnitManager()->getUnit(0)->getMaxAcceleration());
			mDirection.normalize();
			mLinear += mDirection * mStrength;
		}
	}
	return this;
}