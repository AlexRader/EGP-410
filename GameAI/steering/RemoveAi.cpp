#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "RemoveAi.h"
#include "UnitManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

RemoveAi::RemoveAi()
	:GameMessage(REMOVE_AI)
{
}

RemoveAi ::~RemoveAi()
{
}

void RemoveAi::process()
{
	UnitManager* temp = gpGame->getUnitManager();
	//gpGame->getPlayerUnit()->arrive(mPos);
	if (temp->getUnitsLeft() <= 1)
		gpGame->changeEscape();
	else
	{
		srand(time(NULL));
		int tmp = rand() % temp->getSize();
		if (tmp == 0)
			tmp += 1;
		if (temp->getUnit(tmp) != NULL)
			temp->deleteUnit(tmp);
		else
		{
			
			temp->findNearestSequentialUnit();
			if (temp->getUnitsLeft() <= 1)
				gpGame->changeEscape();
		}
	}

	
}