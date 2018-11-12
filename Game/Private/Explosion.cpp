#include "Explosion.h"
#include "COGPhysics.h"
#include "COGExplode.h"

Explosion::Explosion(Hash hash)
	:GameObject(hash)
{
	
}

Explosion::~Explosion()
{
	// Nothing to do here for now
}

void Explosion::Setup(exEngineInterface* pEngine, exVector2& center, float fStartingRadius)
{
	// Put in the essential components into the
	exColor explosionColor;
	explosionColor.SetColor(255, 255, 255);
	
	this->AddComponent(new COGTransform(this, center));

	COGCircleShape* circleShape = new COGCircleShape(pEngine, this, fStartingRadius, explosionColor);
	circleShape->Initialize();
	this->AddComponent(circleShape);

	COGPhysics* physicsComponent = new COGPhysics(pEngine, this, true, 0.0f);
	physicsComponent->Initialize();
	this->AddComponent(physicsComponent);

	COGExplode* explosionComponent = new COGExplode(this, 0.3f);
	explosionComponent->Initialize();
	this->AddComponent(explosionComponent);
}