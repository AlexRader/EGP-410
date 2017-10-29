#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "WeightChange.h"
#include "UnitManager.h"

WeightChange::WeightChange(int choice, float var)
	:GameMessage(WEIGHT_CHANGE)
	, mChoice(choice)
	, mVar(var)
{
}

WeightChange::~WeightChange()
{
}

void WeightChange::process()
{
	//gpGame->getPlayerUnit()->arrive(mPos);

	//gpGame->createUnit(DYNAMIC_ARRIVE, mPos);
	// this function sets the wieghts of the desired variable
	if (gpGame->getUnitManager()->getSize() > 0)
	{
		switch (mChoice)
		{
		case 2:
			gpGame->getUnitManager()->getUnit(0)->setVMatchingWeight(mVar);
			break;
		case 3:
			gpGame->getUnitManager()->getUnit(0)->setSeperation(mVar);
			break;
		case 4:
			gpGame->getUnitManager()->getUnit(0)->setCohesion(mVar);
			break;
		case 5:
			gpGame->getUnitManager()->getUnit(0)->setAlign(mVar);
		}
	}
}