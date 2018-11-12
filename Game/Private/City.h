#pragma once
#include "GameObject.h"

class City : public GameObject
{
public:
	City(Hash hash);
	~City();

	void Setup(exEngineInterface* pEngine, exVector2& position, float& fWidth, float& fHeight);
};