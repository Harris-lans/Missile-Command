#include "Missile.h"
#include "COGPhysics.h"
#include "COGLineShape.h"

// TODO set Velocity and Direction

Missile::Missile(Hash hash)
	:GameObject(hash)
{
	
}

Missile::~Missile()
{
	// Do nothing for now
}

void Missile::Setup(exEngineInterface* pEngine, exVector2& startingPosition, exVector2& direction, exColor& missileColor, float velocity)
{
	this->AddComponent(new COGTransform(this, startingPosition));
	
	COGCircleShape* circleComponent = new COGCircleShape(pEngine, this, 5.0f, missileColor);
	circleComponent->Initialize();
	this->AddComponent(circleComponent);
	
	COGPhysics* physicsComponent = new COGPhysics(pEngine, this, false, velocity);
	physicsComponent->Initialize();
	this->AddComponent(physicsComponent);
	exVector2& facingDirection = physicsComponent->GetFacingDirection();
	facingDirection = direction;

	COGLineShape* lineComponent = new COGLineShape(pEngine, this, startingPosition, missileColor);
	lineComponent->Initialize();
	this->AddComponent(lineComponent);
}