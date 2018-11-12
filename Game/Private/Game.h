//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "City.h"
#include "Silo.h"
#include "COGInputReader.h"
#include "COGEnemyMissileLauncher.h"
#include <vector>
#include <string>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

	void						InitializeGame();

	bool						CheckIfCitiesAreDestroyed();

private:

	GameObjectHandle			mPlayer;
	GameObjectHandle			mEnemy;
	COGEnemyMissileLauncher*	mEnemyLauncher;
	exVector2					mPlayer1ScorePosition;
	exVector2					mPlayer2ScorePosition;

	exEngineInterface*			mEngine;

	GameObjectManager*			mGameObjectManager;
	InputManager*				mInputManager;
	COGArmory*					mArmory;

	std::vector<Hash>			mCities;

	bool						mGameOver;
	std::string					mGameOverText;
	exVector2					mGameOverTextPosition;

	exColor						mScoreFontColor;

	int							mFontID;

	exVector2					mTextPosition;

};
