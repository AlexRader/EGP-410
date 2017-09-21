#pragma once

#include <string>
#include <Trackable.h>

using namespace std;

enum EventType
{
	CLICK_EVENT,
	ESCAPE_EVENT
};

const string EVENT_NAMES[2] =	{	"Click Event", "Escape Event"};

class Event : public Trackable
{
private:
	EventType mType;

public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; };
	const string& getEventName() const;
};