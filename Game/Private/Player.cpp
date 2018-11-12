#include "Player.h"
#include "COGLineCircleShape.h"
#include "COGInputReader.h"

Player::Player(Hash hash)
	:GameObject(hash)
{
	// Nothing for now
}

Player::~Player()
{
	// Nothing to do here for now
}

void Player::Setup(exEngineInterface* pEngine)
{
	exColor reticleColor;
	reticleColor.SetColor(255,255,255);

	this->AddComponent(new COGTransform(this, {0 , 0}));
	this->AddComponent(new COGArmory(this));

	COGLineCircleShape* circleComponent = new COGLineCircleShape(pEngine, this, 5.0f, reticleColor);
	circleComponent->Initialize();
	this->AddComponent(circleComponent);

	COGPlayerInputReader* inputComponent = new COGPlayerInputReader(this);
	inputComponent->Initialize();
	this->AddComponent(inputComponent);
}