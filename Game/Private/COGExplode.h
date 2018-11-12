#pragma once
#include "COGCircleShape.h"
#include "GameObjectManager.h"

class COGExplode : public Component
{
public:
	COGExplode(GameObject* pGameObject, float fRateOfExplosion);
	~COGExplode();

	virtual ComponentType GetType() const override;
	virtual void Initialize() override;
	virtual void Destroy() override;

	void Update();

private:
	float						mRateOfExplosion;
	COGCircleShape*				mShapeComponent;
	GameObjectManager*			mGameObjectManager;
	
public:
	const float					MAXIMUM_RADIUS = 50.0f;
	static std::vector<COGExplode*>	mExplosionComponents;
};