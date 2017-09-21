
#include "game.h"
#include "eventSystem.h"
#include "event.h"
#include "ClickEvent.h"
#include "UnitManager.h"

UnitManager::UnitManager() : EventListener()
{
	mPause = false;
	mNumOfUnits = 0;
	gpEventSystem->addListener(CLICK_EVENT, this);
}

UnitManager::~UnitManager()
{
	mPause = false;
	clear();
	mNumOfUnits = 0;
}

/*
void UnitManager::addUnit(Vector2D loc)
{
	KinematicUnit *temp = new KinematicUnit(loc);
	mUnits[mNumOfUnits] = temp;
	mNumOfUnits++;
}

void UnitManager::addUnit(Vector2D loc, Vector2D vel, std::string name)
{
	KinematicUnit *temp = new KinematicUnit(loc, vel, name);
	mUnits[mNumOfUnits] = temp;
	mNumOfUnits++;
}

void UnitManager::deleteUnit(int indexPos)
{
	if (mUnits.find(indexPos) != mUnits.end())
	{
		delete mUnits.at(indexPos);
		mUnits.erase(indexPos);
	}
}

void UnitManager::deleteUnit(KinematicUnit* unit)
{
	int pos = -1;
	std::map<int, KinematicUnit*>::iterator iter;
	iter = mUnits.begin();

	while (iter != mUnits.end() && iter->second != unit)
	{
		if (iter->second == unit)
			pos = iter->first;
		iter++;
	}
	if (iter->second == unit)
		pos = iter->first;
	if (pos != -1)
	{
		delete mUnits.at(pos);
		mUnits.erase(pos);
	}
	
}
*/
KinematicUnit* UnitManager::getUnit(int indexPos)
{
	if (mUnits.find(indexPos) != mUnits.end())
		return mUnits.at(indexPos);
	else
		return nullptr;
}

void UnitManager::clear()
{
	std::map<int, KinematicUnit*>::iterator iter;
	iter = mUnits.begin();

	while (iter != mUnits.end())
	{
		delete iter->second;
		iter++;
	}
	mUnits.clear();
}

void UnitManager::update(float dt)
{
	std::map<int, KinematicUnit*>::iterator iter;
	iter = mUnits.begin();

	if (mPause != true)
	{
		while (iter != mUnits.end())
		{
			iter->second->update(dt);
			iter++;
		}
	}
	//checkOut();

}

/*
void UnitManager::draw()
{
	std::map<int, Unit*>::iterator iter;
	iter = mUnits.begin();

	while (iter != mUnits.end())
	{
		iter->second->draw();
		iter++;
	}
}

void UnitManager::pause()
{
	mPause = !mPause;
}

Unit *  UnitManager::checkHit(int x, int y)
{
	std::map<int, Unit*>::iterator iter;
	iter = mUnits.begin();

	while (iter != mUnits.end())
	{
		float width = iter->second->getAnim()->getSprite().getWidth();
		float height = iter->second->getAnim()->getSprite().getHeight();
		float posX = iter->second->getX();
		float posY = iter->second->getY();
		if (x <= posX + (width) && x >= posX)
		{
			if (y <= posY + height && y >= posY)
			{
				return iter->second;
			}
		}
		iter++;
	}
	return nullptr;
}

void UnitManager::checkOut()
{
	std::map<int, Unit*>::iterator iter;
	iter = mUnits.begin();

		while (iter != mUnits.end())
		{
			if (iter->second->getX() > Game::getGame()->getWidth() || iter->second->getX() < -50)
			{
				deleteUnit(iter->second);
				break;
			}
			if (iter->second->getY() > Game::getGame()->getHeight() || iter->second->getY() < -50)
			{
				deleteUnit(iter->second);
				break;
			}
			iter++;
		}
}
*/

//this needs to be changed to an evet where the player seeks to the target location
/*
void UnitManager::handleEvent(const Event& theEvent)
{
	
	if (theEvent.getType() == CLICK_EVENT)
	{
		ClickEvent clickEvent = static_cast<const ClickEvent&>(theEvent);
		KinematicUnit * checkedUnit =  checkHit(clickEvent.getLocX(), clickEvent.getLocY());
		if (checkedUnit != NULL)
		{
			checkedUnit->setName();
		}
	}
}
*/