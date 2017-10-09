#pragma once

#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include "UnitManager.h"
#include "InputManager.h"
#include "Hud.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <string>

class UnitManager;
class InputManager;
class Hud;

class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class GameMessageManager;
class Timer;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;
const IDType VERTICAL_WALL_SPRITE_ID = 3;
const IDType HORIZANTAL_WALL_SPRITE_ID = 4;


const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game:public Trackable
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline ALLEGRO_FONT* getFont() const { return mpFont; };

	inline Hud* getHud() const { return mpHud; };
	/*
	inline KinematicUnit* getPlayerUnit() { return mpUnit; };//should be someplace else
	inline KinematicUnit* getAIUnit() { return mpAIUnit; };//should be someplace else
	inline KinematicUnit* getAIUnit2() { return mpAIUnit2; };//should be someplace else
*/
	inline UnitManager* getUnitManager() const {return mpUnitManager;};
	inline InputManager* getInputManager() const {return mpInputManager;};

	inline void changeEscape() { mShouldExit = !mShouldExit; };

	void createUnit(const std::string name, Vector2D vec);

	inline void changeDebug() { mDebug = !mDebug; };

private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	GameMessageManager* mpMessageManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	UnitManager* mpUnitManager;
	InputManager* mpInputManager;
	bool mShouldExit, mDebug;
	Hud* mpHud;
	//should be somewhere else
	ALLEGRO_FONT* mpFont;
	ALLEGRO_SAMPLE* mpSample;
	IDType mBackgroundBufferID;
	IDType mPlayerIconBufferID;
	IDType mEnemyIconBufferID;
	IDType mVerticalWallBufferID;
	IDType mHorizontalWallBufferID;


	
	//KinematicUnit* mpUnit;
	//KinematicUnit* mpAIUnit;
	//KinematicUnit* mpAIUnit2;
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

