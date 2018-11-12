#include "COGFriendlyMissile.h"
#include "Explosion.h"
#include <algorithm>

std::vector<COGFriendlyMissile*> COGFriendlyMissile::mFriendlyMissiles;

COGFriendlyMissile::COGFriendlyMissile(exEngineInterface* pEngine, GameObject* pGameObject, exVector2& targetPosition)
	:Component(pGameObject)
{
	mEngine = pEngine;
	mTargetPosition = targetPosition;
	mHasExploded = false;
	mFriendlyMissiles.push_back(this);
	mGameObjectManager = GameObjectManager::GetInstance();
}

COGFriendlyMissile::~COGFriendlyMissile()
{
	Destroy();
}

ComponentType COGFriendlyMissile::GetType() const
{
	return ComponentType::FriendlyMissile;
}

void COGFriendlyMissile::Initialize()
{
	mTransformComponent = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mPhysicsComponent = mGameObject->FindComponent<COGPhysics>(ComponentType::Physics);
	mMissileTrail = mGameObject->FindComponent<COGLineShape>(ComponentType::LineShape);
}

void COGFriendlyMissile::Destroy()
{
	// Removing the component from the static vector
	mFriendlyMissiles.erase(std::remove(mFriendlyMissiles.begin(), mFriendlyMissiles.end(), this), mFriendlyMissiles.end());

	// Removing from the component's list
	mGameObject->RemoveComponent(this);
	
}

void COGFriendlyMissile::Update()
{
	exVector2& position = mTransformComponent->GetPosition();
	exVector2& trailPosition = mMissileTrail->GetEndPoint();
	
	// Updating the endpoint of the missile trail
	trailPosition = position;

	// Check if the missile has reached the target height
	if (!mHasExploded && (position.y < mTargetPosition.y))
	{
		float& velocity = mPhysicsComponent->GetVelocity();
		velocity = 0;

		mHasExploded = true;
		mExplosionHandle = mGameObjectManager->CreateGameObject(GameObjectTypes::Explosion);
		Explosion* explosion = (Explosion*)mExplosionHandle.Get();
		explosion->Setup(mEngine, position, 5.0f);
	}

	else if (mHasExploded)
	{
		// Waiting for the explosion to be destroyed
		if (!mExplosionHandle.IsValid())
		{
			// Destroy self
			mGameObjectManager->DeleteGameObject(mGameObject);
		}
	}
}