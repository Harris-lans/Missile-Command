#include "COGEnemyMissile.h"
#include "GameObjectManager.h"
#include <algorithm>

std::vector<COGEnemyMissile*> COGEnemyMissile::mEnemyMissiles;

COGEnemyMissile::COGEnemyMissile(GameObject* pGameObject)
	:Component(pGameObject)
{
	mEnemyMissiles.push_back(this);
}

COGEnemyMissile::~COGEnemyMissile()
{
	Destroy();
}

ComponentType COGEnemyMissile::GetType() const
{
	return ComponentType::EnemyMissile;
}

void COGEnemyMissile::Initialize()
{
	mTransformComponent = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mMissileTrailComponent = mGameObject->FindComponent<COGLineShape>(ComponentType::LineShape);
}

void COGEnemyMissile::Update()
{
	exVector2& position = mTransformComponent->GetPosition();
	exVector2& trailPosition = mMissileTrailComponent->GetEndPoint();
	trailPosition = position;

	if (position.y > kViewportHeight)
	{
		GameObjectManager* pGameObjectManager = GameObjectManager::GetInstance();
		pGameObjectManager->DeleteGameObject(mGameObject);
	}
}

void COGEnemyMissile::Destroy()
{
	// Removing the component from the static vector
	mEnemyMissiles.erase(std::remove(mEnemyMissiles.begin(), mEnemyMissiles.end(), this), mEnemyMissiles.end());

	// Removing from the component's list
	mGameObject->RemoveComponent(this);
}