#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <sstream>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "GameMessageManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "KinematicUnit.h"
#include "PlayerMoveToMessage.h"

#include "UnitManager.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;

Game::Game()
	:mpGraphicsSystem(NULL)
	, mpGraphicsBufferManager(NULL)
	, mpSpriteManager(NULL)
	, mpLoopTimer(NULL)
	, mpMasterTimer(NULL)
	, mShouldExit(false)
	, mpFont(NULL)
	, mpSample(NULL)
	, mBackgroundBufferID(INVALID_ID)
	, mpUnitManager(NULL)
	, mpInputManager(NULL)
	, mpHud(NULL)
	, mGameWidth(WIDTH)
	, mGameHeight(HEIGHT)
	//,mSmurfBufferID(INVALID_ID)
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	mShouldExit = false;
	mDebug = false;
	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	//startup allegro
	if(!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}

	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->init( mGameWidth, mGameHeight );
	if(!goodGraphics) 
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpSpriteManager = new SpriteManager();

	//startup a lot of allegro stuff

	//load image loader addon
	if( !al_init_image_addon() )
	{
		fprintf(stderr, "image addon failed to load!\n");
		return false;
	}

	//install audio stuff
	if( !al_install_audio() )
	{
		fprintf(stderr, "failed to initialize sound!\n");
		return false;
	}

	if(!al_init_acodec_addon())
	{
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return false;
	}
 
	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "failed to reserve samples!\n");
		return false;
	}

	//should be somewhere else!
	al_init_font_addon();
	if( !al_init_ttf_addon() )
	{
		printf( "ttf font addon not initted properly!\n" ); 
		return false;
	}

	//actually load the font
	mpFont = al_load_ttf_font( "cour.ttf", 20, 0 );
	if( mpFont == NULL )
	{
		printf( "ttf font file not loaded properly!\n" ); 
		return false;
	}

	//show the mouse
	if( !al_hide_mouse_cursor( mpGraphicsSystem->getDisplay() ) )
	{
		printf( "Mouse cursor not able to be hidden!\n" ); 
		return false;
	}

	if( !al_init_primitives_addon() )
	{
		printf( "Primitives addon not added!\n" ); 
		return false;
	}

	//load the sample
	mpSample = al_load_sample( "clapping.wav" );
	if (!mpSample)
	{
		printf( "Audio clip sample not loaded!\n" ); 
		return false;
	}

	mpHud = new Hud();
	mpInputManager = new InputManager();
	mpInputManager->init();
	mpUnitManager = new UnitManager();
	mpMessageManager = new GameMessageManager();

	//load buffers
	mBackgroundBufferID = mpGraphicsBufferManager->loadBuffer("wallpaper.bmp");
	mPlayerIconBufferID = mpGraphicsBufferManager->loadBuffer("arrow.bmp");
	mEnemyIconBufferID = mpGraphicsBufferManager->loadBuffer("enemy-arrow.bmp");
	mVerticalWallBufferID = mpGraphicsBufferManager->loadBuffer("vertical.bmp");
	mHorizontalWallBufferID = mpGraphicsBufferManager->loadBuffer("horizontal.bmp");
	
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer( mPlayerIconBufferID );
	Sprite* pArrowSprite = NULL;
	if( pPlayerBuffer != NULL )
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite( PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, pPlayerBuffer->getWidth(), pPlayerBuffer->getHeight() );
	}
	
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer( mEnemyIconBufferID );
	Sprite* pEnemyArrow = NULL;
	if( pAIBuffer != NULL )
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite( AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, pAIBuffer->getWidth(), pAIBuffer->getHeight() );
	}

	GraphicsBuffer* pVerticalBuffer = mpGraphicsBufferManager->getBuffer( mVerticalWallBufferID );
	Sprite* pVerticalSprite = NULL;
	if (pVerticalBuffer != NULL)
	{
		pVerticalSprite = mpSpriteManager->createAndManageSprite(mVerticalWallBufferID, pVerticalBuffer, 0, 0, pVerticalBuffer->getWidth(), pVerticalBuffer->getHeight());
	}

	GraphicsBuffer* pHorizontalBuffer = mpGraphicsBufferManager->getBuffer( mHorizontalWallBufferID );
	Sprite* pHorizontalSprite = NULL;
	if (pHorizontalBuffer != NULL)
	{
		pHorizontalSprite = mpSpriteManager->createAndManageSprite(mHorizontalWallBufferID, pHorizontalBuffer, 0, 0, pHorizontalBuffer->getWidth(), pHorizontalBuffer->getHeight());
	}

	srand(static_cast <unsigned> (time(0)));
	//setup units
	Vector2D pos( 0.0f, 0.0f );
	Vector2D playerPos(500.0f, 500.0f);
	Vector2D vel( 0.0f, 0.0f );

	mpUnitManager->addUnitPlayer(pArrowSprite, playerPos, 1, vel, 0.0f, "Player", 200.0f, 10.0f);

	mpUnitManager->addUnitWall(pHorizontalSprite, Vector2D(0.0f, mpGraphicsSystem->getHeight() - pHorizontalSprite->getHeight()), 0, vel, 0.0, WALL_HOR, 0.0f, 0.0f);
	mpUnitManager->addUnitWall(pVerticalSprite, Vector2D(mpGraphicsSystem->getWidth() - pVerticalSprite->getWidth(), 0.0f), 0, vel, 0.0, WALL_VERT, 0.0f, 0.0f);
	mpUnitManager->addUnitWall(pVerticalSprite, pos, 0, vel, 0.0, WALL_VERT, 0.0f, 0.0f);
	mpUnitManager->addUnitWall(pHorizontalSprite, pos, 0, vel, 0.0, WALL_HOR, 0.0f, 0.0f);
	
	return true;
}

void Game::cleanup()
{

	//delete units
	delete mpUnitManager;
	mpUnitManager = NULL;
	delete mpInputManager;
	mpInputManager = NULL;

	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpMessageManager;
	mpMessageManager = NULL;


	delete mpHud;
	mpHud = NULL;

	al_destroy_sample(mpSample);
	mpSample = NULL;
	al_destroy_font(mpFont);
	mpFont = NULL;

	//shutdown components
	al_uninstall_audio();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();

}

void Game::beginLoop()
{
	mpLoopTimer->start();
}
	
void Game::processLoop()
{
	//update units
	mpUnitManager->update(LOOP_TARGET_TIME / 1000.0f);

	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite( BACKGROUND_SPRITE_ID );
	pBackgroundSprite->draw( *(mpGraphicsSystem->getBackBuffer()), 0, 0 );

	//draw units
	mpUnitManager->draw(GRAPHICS_SYSTEM->getBackBuffer());
	
	if (mDebug == true)
	{
		//al_draw_text(getFont(), al_map_rgb(255, 255, 255), 50, 50, ALLEGRO_ALIGN_CENTRE, "+: Increases value");
		mpHud->draw();
	}

	mpMessageManager->processMessagesForThisframe();

	mpInputManager->update();

	mpGraphicsSystem->swap();
}

bool Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( LOOP_TARGET_TIME );
	return mShouldExit;
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

void Game::createUnit(const std::string name, Vector2D vec)
{
	mpUnitManager->addUnit(mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), vec, 1, Vector2D(genRandomFloat(), genRandomFloat()), 0.0f, name, 180.0f, 100.0f);
}
