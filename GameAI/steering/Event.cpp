#include "Event.h"

Event::Event(EventType type)
{
	mType = type;
}

Event::~Event()
{
}

const string& Event::getEventName() const
{
	return EVENT_NAMES[mType];
}
