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
	if (temp->getSize() <= 0)
		gpGame->changeEscape();
	else
	{
		srand(unsigned(time(NULL)));
		int tmp = rand() % temp->getSize();
			temp->deleteUnit(tmp);
	}
}