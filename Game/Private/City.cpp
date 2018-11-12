#include "City.h"
#include "COGDestroyOnCollisionWith.h"

City::City(Hash hash)
	:GameObject(hash)
{
	// Do nothing
}

City::~City()
{
	// Do nothing for now
}

void City::Setup(exEngineInterface* pEngine, exVector2& position, float& fWidth, float& fHeight)
{
	// Add necessary components
	exColor cityColor;
	cityColor.SetColor(0, 0, 255, 255);

	this->AddComponent(new COGTransform(this, position));
	
	COGBoxShape* boxComponent = new COGBoxShape(pEngine, this, fWidth, fHeight, cityColor);
	boxComponent->Initialize();
	this->AddComponent(boxComponent);

	COGPhysics* physicsComponent = new COGPhysics(pEngine, this, true, 0.0f);
	physicsComponent->Initialize();
	this->AddComponent(physicsComponent);


	COGDestroyOnCollisionWith* collisionEvent = new COGDestroyOnCollisionWith(this, ComponentType::EnemyMissile);
	collisionEvent->Initialize();
	this->AddComponent(collisionEvent);
}