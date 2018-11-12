#pragma once
#include "COGTransform.h"
#include "GameObjectManager.h"

class COGEnemyMissileLauncher : public Component
{
public:
	COGEnemyMissileLauncher(exEngineInterface* pEngine, GameObject* pGameObject, int iMaximumNumberOfMissilesToLaunch, std::vector<GameObject*>& pGameObjects);
	~COGEnemyMissileLauncher();

	virtual ComponentType GetType() const;
	virtual void Initialize() override;
	virtual void Update();

private:
	bool CheckIfTargetsAlive();
	void FireMissile(exVector2& startingPosition, exVector2& direction);

	int							mMaximumNumberOfMissilesToLaunch;
	GameObjectManager*			mGameObjectManager;
	GameObjectHandle			mGameObjectHandle;
	exEngineInterface*			mEngine;
	std::vector<COGTransform*>	mTargetPositions;
	std::vector<GameObject*>	mTargetObjects;
	exColor						mMissileColor;
};