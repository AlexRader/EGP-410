#pragma once

#include "Trackable.h"

class Event;

class EventListener : public Trackable
{
public:
	EventListener();
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;
private:

};
/*
EventListener::EventListener()
{
}

EventListener::~EventListener()
{
}

class EventListener : public Trackable
{
public:
	EventListener();
	virtual ~EventListener();

	virtual void handleEvent( const Event& theEvent ) = 0;

private:

};*/