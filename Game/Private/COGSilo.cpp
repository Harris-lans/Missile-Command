#include "COGSilo.h"
#include "COGFriendlyMissile.h"
#include "Missile.h"
#include <algorithm>

std::vector<COGSilo*> COGSilo::mSiloComponents;

COGSilo::COGSilo(exEngineInterface* pEngine, GameObject* pGameObject, int iNumberOfMissiles)
	:Component(pGameObject)
{
	// Initializing the number of Missiles
	mMissilesLeft = iNumberOfMissiles;
	mSiloComponents.push_back(this);
	mGameObjectManager = GameObjectManager::GetInstance();
	mEngine = pEngine;
	mMissileColor.SetColor(0, 255, 0);
}

COGSilo::~COGSilo()
{
	Destroy();
}

ComponentType COGSilo::GetType() const
{
	return ComponentType::Silo;
}

void COGSilo::Initialize()
{
	mTransformComponent = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mTextComponent = mGameObject->FindComponent<COGTextRenderer>(ComponentType::TextRenderer);
}

void COGSilo::Destroy()
{
	// Removing the component from the static vector
	mSiloComponents.erase(std::remove(mSiloComponents.begin(), mSiloComponents.end(), this), mSiloComponents.end());

	// Removing from the component's list
	mGameObject->RemoveComponent(this);
	Console::LogString("Deleted Silo Component! \n");
}

void COGSilo::FireMissile(exVector2& targetPosition)
{
	if (mMissilesLeft > 0)
	{
		// Calculating the direction to fire the missile in
		exVector2& currentPosition = mTransformComponent->GetPosition();
		exVector2 direction = { (targetPosition.x - currentPosition.x) , (targetPosition.y - currentPosition.y) };
		direction.Normalize();

		// Firing the missile
		GameObjectHandle missileHandle = mGameObjectManager->CreateGameObject(GameObjectTypes::Missile);
		Missile* missile = (Missile*)missileHandle.Get();
		missile->Setup(mEngine, currentPosition, direction, mMissileColor, 150.0f);

		// Adding the friendly missile component
		COGFriendlyMissile* friendlyMissileComponent = new COGFriendlyMissile(mEngine, missile, targetPosition);
		friendlyMissileComponent->Initialize();
		missile->AddComponent(friendlyMissileComponent);

		// Deducting the number of missile
		--mMissilesLeft;
	}
}

void COGSilo::Update()
{
	// Updating the text value every update
	std::string& text = mTextComponent->GetText();
	text = std::to_string(mMissilesLeft);
}

bool COGSilo::CanFire()
{
	return (mMissilesLeft > 0);
}