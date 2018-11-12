#pragma once
#include "GameObject.h"

class Missile : public GameObject
{
public:
	Missile(Hash hash);
	~Missile();

	void Setup(exEngineInterface* pEngine, exVector2& startingPosition, exVector2& direction, exColor&, float velocity);
};