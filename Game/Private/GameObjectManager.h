#pragma once
#include "Singleton.h"
#include "GameObjectHandle.h"
#include <vector>

enum class GameObjectTypes
{
	EmptyGameObject = 0,
	Missile,
	City,
	Explosion,
	Player,
	Silo
};

extern std::hash<std::string> string_hash;

class GameObjectManager : public Singleton<GameObjectManager>
{
private:

	GameObjectInventory * mGameObjectInventory;
	std::vector<GameObject*> mStaleObjects;
	exEngineInterface* mEngine;

public:

	GameObjectManager();
	~GameObjectManager();

	GameObjectHandle CreateGameObject(GameObjectTypes gameObjectType);
	void DeleteGameObject(GameObject* pGameObject);
	void ClearAllGameObjects();

	void Initialize(exEngineInterface* pEngine);

	void Update(float fDeltaTime);
	void Render();
};
