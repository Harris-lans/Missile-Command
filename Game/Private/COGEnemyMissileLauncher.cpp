#include "COGEnemyMissileLauncher.h"
#include "COGDestroyOnCollisionWith.h"
#include "COGEnemyMissile.h"
#include "COGExplode.h"
#include "Missile.h"
#include "City.h"
#include <time.h>

const int MAXIMUM_NUMBER_OF_MISSILES_TO_LAUNCH = 6;

COGEnemyMissileLauncher::COGEnemyMissileLauncher(exEngineInterface* pEngine, GameObject* pGameObject, int iMaximumNumberOfMissilesToLaunch, std::vector<GameObject*>& pTargetObjects)
	:Component(pGameObject)
{
	mMaximumNumberOfMissilesToLaunch = iMaximumNumberOfMissilesToLaunch;
	mEngine = pEngine;
	mTargetObjects = pTargetObjects;
	srand(time(NULL));
	mGameObjectManager = GameObjectManager::GetInstance();
	mMissileColor.SetColor(255, 0, 0);

}

COGEnemyMissileLauncher::~COGEnemyMissileLauncher()
{
	Destroy();
}

void COGEnemyMissileLauncher::Initialize()
{
	GameObjectHandle gameObjectHandle;
	for (GameObject* pGameObject : mTargetObjects)
	{
		gameObjectHandle.SetHash(pGameObject->mHash);
		if (gameObjectHandle.IsValid())
		{
			COGTransform* pTransformComponent = pGameObject->FindComponent<COGTransform>(ComponentType::Transform);
			if (pTransformComponent != nullptr)
			{
				mTargetPositions.push_back(pTransformComponent);
			}
		}
	}
}

ComponentType COGEnemyMissileLauncher::GetType() const
{
	return ComponentType::EnemyMissileLauncher;
}


void COGEnemyMissileLauncher::Update()
{
	srand(time(NULL));
	if (COGEnemyMissile::mEnemyMissiles.size() == 0)
	{
		// Launch a random number of missiles
		int numberOfMissilesToLaunch = rand() % mMaximumNumberOfMissilesToLaunch + 1;

		for (int i = 0; i < mMaximumNumberOfMissilesToLaunch; i++)
		{
			// Choosing a random start position
			exVector2 startingPosition = { (rand() % kViewportWidth ) , 0 };
			exVector2 target;

			// Choosing a random target
			while (CheckIfTargetsAlive())
			{
				GameObjectHandle gameObjectHandle;
				int randomTarget = rand() % mTargetObjects.size();
				gameObjectHandle.SetHash(mTargetObjects[randomTarget]->mHash);
				if (gameObjectHandle.IsValid())
				{
					target = mTargetPositions[randomTarget]->GetPosition();
					exVector2 direction = { (target.x - startingPosition.x) , (target.y) };
					direction.Normalize();

					// Firing the missile
					mGameObjectHandle = mGameObjectManager->CreateGameObject(GameObjectTypes::Missile);
					Missile* missile = (Missile*)mGameObjectHandle.Get();
					missile->Setup(mEngine, startingPosition, direction, mMissileColor, 80.0f);
					COGEnemyMissile* enemyMissileComponent = new COGEnemyMissile(missile);
					enemyMissileComponent->Initialize();
					missile->AddComponent(enemyMissileComponent);

					COGDestroyOnCollisionWith* collisionEvent = new COGDestroyOnCollisionWith(missile, ComponentType::Explosion);
					collisionEvent->Initialize();
					missile->AddComponent(collisionEvent);	

					collisionEvent = new COGDestroyOnCollisionWith(missile, ComponentType::BoxShape);
					collisionEvent->Initialize();
					missile->AddComponent(collisionEvent);

					break;
				}
			}
		}
	}
}

void FireMissile(exVector2& startingPosition, exVector2& direction)
{

}

bool COGEnemyMissileLauncher::CheckIfTargetsAlive()
{
	GameObjectHandle gameObjectHandle;
	for (GameObject* pGameObject : mTargetObjects)
	{
		gameObjectHandle.SetHash(pGameObject->mHash);
		if (gameObjectHandle.IsValid())
		{
			return true;
		}
	}
	return false;
}