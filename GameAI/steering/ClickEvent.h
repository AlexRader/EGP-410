#pragma once
#include "event.h"

class ClickEvent : public Event
{
private:
	int mX, mY;

public:
	ClickEvent(int& locX, int& locY);
	~ClickEvent();

	int getLocX();
	int getLocY();
};