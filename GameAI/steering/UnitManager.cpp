
#include "game.h"
#include "eventSystem.h"
#include "event.h"
#include "ClickEvent.h"
#include "UnitManager.h"

UnitManager::UnitManager()
{
	mPause = false;

	//gpEventSystem->addListener(CLICK_EVENT, this);
}

UnitManager::~UnitManager()
{
	clear();
}


void UnitManager::addUnit(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, std::string name, float maxVelocity, float maxAcceleration)
{
	KinematicUnit *temp = new KinematicUnit(pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration);

	if (DYNAMIC_ARRIVE == name)
	{
		//temp->dynamicArrive(getUnit(0));
		temp->wander();
	}
	else if (DYNAMIC_SEEK == name)
	{
		//temp->dynamicSeek(getUnit(0));
		temp->wander();

	}
	mUnits.push_back(temp);
}
/*
void UnitManager::addUnit(Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f, std::string name)
{
	KinematicUnit *temp = new KinematicUnit(loc, vel, name);
	mUnits[mNumOfUnits] = temp;
	mNumOfUnits++;
}
*/
void UnitManager::deleteUnit(unsigned int indexPos)
{
	if (indexPos < 0 || indexPos >= mUnits.size())
		return;
	delete mUnits.at(indexPos);
	mUnits.erase(mUnits.begin() + indexPos);
}
/*
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
		return mUnits.at(indexPos);
}

void UnitManager::clear()
{

	for each (KinematicUnit* unit in mUnits)
		delete unit;
	
	mUnits.clear();
}

void UnitManager::update(float dt)
{
	/*
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
*/
	for each (KinematicUnit* unit in mUnits)
		unit->update(dt);
	//checkOut();

}


void UnitManager::draw(GraphicsBuffer* pBuffer)
{
	/*
	std::map<int, KinematicUnit*>::iterator iter;
	iter = mUnits.begin();

	while (iter != mUnits.end())
	{
		iter->second->draw(pBuffer);
		iter++;
	}
*/
	for each (KinematicUnit* unit in mUnits)
		unit->draw(pBuffer);
}