//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Private/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"
#include <time.h>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Missile Commander 2.0";
const float CITY_HEIGHT = 30.0f;
const float CITY_WIDTH = 100.0f;
const int MAXIUMUM_NUMBER_OF_ENEMY_MISSILES = 2;
//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
	,mGameOver(false)
	,mGameOverText("")
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
	mGameObjectManager->ClearAllGameObjects();
	mGameObjectManager->DeleteInstance();
	mInputManager->DeleteInstance();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	srand(time(NULL));

	mEngine = pEngine;
	mGameObjectManager = GameObjectManager::GetInstance();
	mGameObjectManager->Initialize(mEngine);
	mInputManager = InputManager::GetInstance();

	mFontID = mEngine->LoadFont("randomFont.ttf", 40.0f);

	mGameOverTextPosition = { (kViewportWidth / 2) , (kViewportHeight / 2) };
	mScoreFontColor.SetColor(200, 200, 200, 255);
	InitializeGame();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 0;
	color.mColor[1] = 0;
	color.mColor[2] = 0;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{		
		
	if (!mGameOver)
	{
		mInputManager->Update();
		mGameObjectManager->Update(fDeltaT);
		mGameObjectManager->Render();
		mEnemyLauncher->Update();

		if (mArmory->SilosOutOfMissiles())
		{
			std::string text = "Silos Out of Missiles!";
			const char* gameOverTextChar = text.c_str();
			mEngine->DrawText(mFontID, { kViewportWidth / 5 , kViewportHeight / 2 }, gameOverTextChar, mScoreFontColor, 10);
		}

		if (CheckIfCitiesAreDestroyed())
		{
			mGameOver = true;
			mGameObjectManager->ClearAllGameObjects();
		}
	}
	else
	{
		mGameOverText = "All your cities have been Destroyed!";
		const char* gameOverTextChar = mGameOverText.c_str();
		mEngine->DrawText(mFontID, { kViewportWidth / 5 - 100, kViewportHeight / 2 }, gameOverTextChar, mScoreFontColor, 10);
	}
}


bool MyGame::CheckIfCitiesAreDestroyed()
{
	GameObjectHandle cityHandle;
	for (Hash hash : mCities)
	{
		cityHandle.SetHash(hash);
		if (cityHandle.IsValid())
		{
			return false;
		}
	}
	return true;
}

void MyGame::InitializeGame()
{
	GameObjectHandle gameObjectHandle;

	// Setting up Player
	mPlayer = mGameObjectManager->CreateGameObject(GameObjectTypes::Player);
	Player* player = (Player*)mPlayer.Get();
	player->Setup(mEngine);

	// Creating Silo
	mArmory = player->FindComponent<COGArmory>(ComponentType::Armory);

	// Silo - 1
	exVector2 siloPosition = { 80 , (kViewportHeight - CITY_HEIGHT) };
	float fontSize = 25;
	GameObjectHandle silo = mGameObjectManager->CreateGameObject(GameObjectTypes::Silo);
	Silo* pSilo = (Silo*)silo.Get();
	pSilo->Setup(mEngine, siloPosition, fontSize);
	mArmory->RegisterSilo(1, pSilo->FindComponent<COGSilo>(ComponentType::Silo));

	// Silo - 2
	siloPosition.x += 220;
	silo = mGameObjectManager->CreateGameObject(GameObjectTypes::Silo);
	pSilo = (Silo*)silo.Get();
	pSilo->Setup(mEngine, siloPosition, fontSize);
	mArmory->RegisterSilo(2, pSilo->FindComponent<COGSilo>(ComponentType::Silo));

	// Silo - 3
	siloPosition.x += 220;
	silo = mGameObjectManager->CreateGameObject(GameObjectTypes::Silo);
	pSilo = (Silo*)silo.Get();
	pSilo->Setup(mEngine, siloPosition, fontSize);
	mArmory->RegisterSilo(3, pSilo->FindComponent<COGSilo>(ComponentType::Silo));

	// Creating Cities
	float cityWidth = CITY_WIDTH;
	float cityHeight = CITY_HEIGHT;
	std::vector<GameObject*> cities;
	// City - 1
	exVector2 cityPosition = { (kViewportWidth / 6) , (kViewportHeight - CITY_HEIGHT) };
	GameObjectHandle pCity = mGameObjectManager->CreateGameObject(GameObjectTypes::City);
	City* city = (City*) pCity.Get();
	city->Setup(mEngine, cityPosition, cityWidth, cityHeight);
	cities.push_back(city);
	mCities.push_back(city->mHash);
	
	// City - 2
	cityPosition.x += 220;
	pCity = mGameObjectManager->CreateGameObject(GameObjectTypes::City);
	city = (City*)pCity.Get();
	city->Setup(mEngine, cityPosition, cityWidth, cityHeight);
	cities.push_back(city);
	mCities.push_back(city->mHash);

	// City - 3
	cityPosition.x += 220;
	pCity = mGameObjectManager->CreateGameObject(GameObjectTypes::City);
	city = (City*)pCity.Get();
	city->Setup(mEngine, cityPosition, cityWidth, cityHeight);
	cities.push_back(city);
	mCities.push_back(city->mHash);

	// Creating the Enemy Missile Launcher
	mEnemy = mGameObjectManager->CreateGameObject(GameObjectTypes::EmptyGameObject);
	GameObject* pEnemy = mEnemy.Get();
	mEnemyLauncher = new COGEnemyMissileLauncher(mEngine, pEnemy, MAXIUMUM_NUMBER_OF_ENEMY_MISSILES, cities);
	mEnemyLauncher->Initialize();
	pEnemy->AddComponent(mEnemyLauncher);

}