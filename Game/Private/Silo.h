#pragma once
#include "GameObject.h"

class Silo : public GameObject
{
public:
	Silo(Hash hash);
	~Silo();

	void Setup(exEngineInterface* pEngine, exVector2& position, float& size);
};