#include "Game.h"
#include "GameApp.h"
#include "Defines.h"
#include "InputManager.h"
#include <allegro5/allegro.h>
#include "GameMessageManager.h"
#include <sstream>

#include "Vector2D.h"

#include <allegro5/allegro_font.h>
#include "PathToMessage.h"
#include "PathDisplayAstarMessage.h"
#include "PathDisplayDijkstraMessage.h"

InputManager::InputManager()
{
	mInitialized = false;
	pGame = dynamic_cast<GameApp*>(gpGame);
	mPosStart = NULL;
	mPosEnd = NULL;
}


InputManager::~InputManager()
{
	if (mInitialized)
		cleanUp();
}

void InputManager::init()
{
	if (mInitialized)
		cleanUp();

	//initialize systems
	if (!al_init())
	{
		std::cout << "This could be a problem... Allegro didn't initialize properly.\n";
	}

	if (!al_install_keyboard())
	{
		std::cout << "This could be a problem... Allegro couldn't initialize the keyboard.\n";
	}

	if (!al_install_mouse())
	{
		std::cout << "This could be a problem... Allegro couldn't initialize the Mouse addon.\n";
	}

	mInitialized = true;
	mSwitched = 0.0f;
}

void InputManager::cleanUp()
{
	if (mInitialized)
	{
		mInitialized = false;
		al_uninstall_keyboard();
		al_uninstall_mouse();
	}
}

void InputManager::update()
{
	//get mouse state
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	
	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		Vector2D pos(mouseState.x, mouseState.y);
		setStart(pos);
		if (getEnd() != NULL)
		{
			GameMessage* pMessage = new PathToMessage(pos, getEnd());
			pGame->getMessageManager()->addMessage(pMessage, 0);
		}
	}
	if (al_mouse_button_down(&mouseState, 2))//right mouse click
	{
		Vector2D pos(mouseState.x, mouseState.y);
		setEnd(pos);
		if (getStart() != NULL)
		{
			GameMessage* pMessage = new PathToMessage(getStart(), pos);
			pGame->getMessageManager()->addMessage(pMessage, 0);
		}
	}

	
	//all this should be moved to InputManager!!!
	{
		//get current keyboard state
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		al_get_keyboard_state(&mCurrentState);
		//if escape key was down then exit the loop
		
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
		{
			//GameMessage* pMessage = new EscapeMessage();
			//pGame->getMessageManager()->addMessage(pMessage, 0);
		}

		// theses next 3 functions just change value of the three weights for flocking
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_A) && !al_key_down(&mPreviousState, ALLEGRO_KEY_A))
		{
			GameMessage* pMessage = new PathDisplayAstarMessage("ASTAR");
			pGame->getMessageManager()->addMessage(pMessage, 0);
		}
		if (al_key_down(&mCurrentState, ALLEGRO_KEY_D) && !al_key_down(&mPreviousState, ALLEGRO_KEY_D))
		{
			GameMessage* pMessage = new PathDisplayDijkstraMessage("Dijkstra");
			pGame->getMessageManager()->addMessage(pMessage, 0);
		}

		mPreviousState = mCurrentState;
	}
}