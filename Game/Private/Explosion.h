#pragma once
#include "GameObject.h"

const float RATE_OF_GROWTH_OF_EXPLOSION = 0.5f;
const float MAXIMUM_RADIUS_OF_EXPLOSION = 10.0f;

class Explosion : public GameObject
{
public:
	Explosion(Hash hash);
	~Explosion();

	void Setup(exEngineInterface* pEngine, exVector2& startingPosition, float fStartingRadius);
};