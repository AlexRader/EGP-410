#pragma once

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	ARRIVE_SPAWN = 1,
	SEEK_SPAWN = 2, 
	REMOVE_AI = 3,
	DISPLAY_DEBUG = 4,
	V_CONTROL = 5,
	R_CONTROL = 6,
	A_CONTROL = 7,
	ESCAPE_MESSAGE = 8,
	PLUS_MINUS = 9,
	BOIDS_SPAWN = 10,
	WEIGHT_CHANGE = 11
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

