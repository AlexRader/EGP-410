#include "KinematicUnit.h"
#include "VelocityMatchingSteering.h"
#include <algorithm> 

VelocityMatchingSteering::VelocityMatchingSteering(KinematicUnit* pMover)
	:mpMover(pMover)
	, mRadius(0.0f)
	, mCount(0)
{
	setWeight(0.7f);
}


Steering* VelocityMatchingSteering::getSteering()
{
	mRadius = gpGame->getUnitManager()->getRadius();
	mStored = Vector2D(0.0f, 0.0f);
	Vector2D direction, temp;
	float distance;
	//checks all units
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); ++i)
	{
			direction = gpGame->getUnitManager()->getUnit(i)->getPosition() - mpMover->getPosition();
			distance = direction.getLength();
			// if unit is within range
			if (distance < mRadius)
			{
				temp = gpGame->getUnitManager()->getUnit(i)->getVelocity() - mpMover->getVelocity();
				//temp /= TIME_TO_TARGET;
				mStored += temp;
				mCount++;
			}
			// if more than one is within range
			if (mCount > 0)
			{
				mStored /= mCount; // averages it
				mLinear = mStored;
				mCount = 0;
			}
			//normalize the mLinear
			if (mLinear.getLength() > mpMover->getMaxAcceleration())
			{
				mLinear.normalize();
				mLinear *= mpMover->getMaxAcceleration();
			}
	}
	//mAngular = 0;
	return this;
}