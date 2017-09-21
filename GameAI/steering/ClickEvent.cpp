#include "ClickEvent.h"

ClickEvent::ClickEvent(int & locX, int & locY) : Event(CLICK_EVENT)
{
	mX = locX;
	mY = locY;
}

ClickEvent::~ClickEvent()
{
}

int ClickEvent::getLocX()
{
	return mX;
}

int ClickEvent::getLocY()
{
	return mY;
}