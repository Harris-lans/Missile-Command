#include "GameObjectManager.h"
#include "COGInputReader.h"
#include "COGPhysics.h"
#include "COGEnemyMissile.h"
#include "Player.h"
#include "Explosion.h"
#include "Missile.h"
#include "City.h"
#include "Silo.h"
#include "COGFriendlyMissile.h"
#include "COGExplode.h"
#include <functional>

// Using an alias for the hash functions for strings
std::hash<std::string> string_hash;

// Initializing the singleton
GameObjectManager* Singleton<GameObjectManager>::existingInstance = nullptr;

GameObjectManager::GameObjectManager()
{
	// Nothing to do here for now
}

GameObjectManager::~GameObjectManager()
{
	// Nothing to do here for now
	mGameObjectInventory->DeleteInstance();
}


void GameObjectManager::Initialize(exEngineInterface* pEngine)
{
	mEngine = pEngine;
	mGameObjectInventory = GameObjectInventory::GetInstance();
}

GameObjectHandle GameObjectManager::CreateGameObject(GameObjectTypes gameObjectType)
{
	GameObjectHandle gameObjectHandle;

	// Creating the requested game object and returning a handle to it
	switch (gameObjectType)
	{
	case GameObjectTypes::EmptyGameObject:
		{
			GameObject * gameObject = new GameObject(string_hash(std::to_string(GameObject::gameObjectNumber) + "empty-game-object-"));
			mGameObjectInventory->Register(gameObject);
			gameObjectHandle.SetHash(gameObject->mHash);
			return gameObjectHandle;
		}
	case GameObjectTypes::Missile:
		{
			Missile* missile = new Missile(string_hash(std::to_string(GameObject::gameObjectNumber) + "missile"));
			mGameObjectInventory->Register((GameObject*)missile);
			gameObjectHandle.SetHash(missile->mHash);
			return gameObjectHandle;
		}
	case GameObjectTypes::City:
		{
			City* city = new City(string_hash(std::to_string(GameObject::gameObjectNumber) + "city"));
			mGameObjectInventory->Register((GameObject*)city);
			gameObjectHandle.SetHash(city->mHash);
			return gameObjectHandle;
		}
	case GameObjectTypes::Explosion:
		{
			Explosion* explosion = new Explosion(string_hash(std::to_string(GameObject::gameObjectNumber) + "explosion"));
			mGameObjectInventory->Register((GameObject*)explosion);
			gameObjectHandle.SetHash(explosion->mHash);
			return gameObjectHandle;
		}
	case GameObjectTypes::Player:
		{
			Player* player = new Player(string_hash(std::to_string(GameObject::gameObjectNumber) + "player"));
			mGameObjectInventory->Register((GameObject*)player);
			gameObjectHandle.SetHash(player->mHash);
			return gameObjectHandle;
		}
	case GameObjectTypes::Silo:
		{
			Silo* silo = new Silo(string_hash(std::to_string(GameObject::gameObjectNumber) + "silo"));
			mGameObjectInventory->Register((GameObject*)silo);
			gameObjectHandle.SetHash(silo->mHash);
			return gameObjectHandle;
		}
	default:
		return gameObjectHandle;
	}
}

void GameObjectManager::DeleteGameObject(GameObject* pGameObject)
{	
	// Passing the gameobject pointer
	mStaleObjects.push_back(pGameObject);
}


void GameObjectManager::ClearAllGameObjects()
{
	mGameObjectInventory->ClearGameObjectInventory();
}


// Updating and rendering the gameobject
void GameObjectManager::Update(float fDeltaTime)
{
	// Updating the physics component and the input reader components

	for (COGPhysics* pPhysicsComponent : COGPhysics::mPhysicsComponents)
	{
		pPhysicsComponent->Update(fDeltaTime);
	}

	for (COGPlayerInputReader* pInputReaderComponent : COGPlayerInputReader::mInputReaderComponents)
	{
		pInputReaderComponent->Update();
	}

	// Updating the Explosions and Missiles and Silos
	for (COGSilo* silo : COGSilo::mSiloComponents)
	{
		silo->Update();
	}

	for (COGExplode* explosion : COGExplode::mExplosionComponents)
	{
		explosion->Update();
	}

	for (COGFriendlyMissile* friendlyMissile : COGFriendlyMissile::mFriendlyMissiles)
	{
		friendlyMissile->Update();
	}

	for (COGEnemyMissile* enemyMissile : COGEnemyMissile::mEnemyMissiles)
	{
		enemyMissile->Update();
	}

	// Cleaning up all the deleted gameObjects
	for (GameObject* pGameObject : mStaleObjects)
	{
		mGameObjectInventory->Unregister(pGameObject);
	}
}

void GameObjectManager::Render()
{
	// Rendering all the shape components
	for (COGShape* pShapeComponent : COGShape::mShapeComponents)
	{
		pShapeComponent->Render();
	}
}