#pragma once

#include "Trackable.h"
#include <allegro5/allegro.h>
#include "Vector2D.h"

class InputManager : public Trackable
{
public:
	InputManager();
	~InputManager();

	void init();
	void cleanUp();

	void update();

	inline void setSwitch(float var) { mSwitched = var; };

	//starts and end points
	inline void setStart(Vector2D start) { mPosStart = start; };
	inline void setEnd(Vector2D end) { mPosEnd = end; };

	inline Vector2D getStart() { return mPosStart; };
	inline Vector2D getEnd() { return mPosEnd; };



private:
	bool mInitialized;
	float mSwitched;
	ALLEGRO_KEYBOARD_STATE mPreviousState;
	ALLEGRO_KEYBOARD_STATE mCurrentState;

	GameApp* pGame;

	Vector2D mPosStart, mPosEnd;

};