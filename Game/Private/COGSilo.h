#pragma once
#include "COGTransform.h"
#include "COGTextRenderer.h"
#include "GameObjectManager.h"

class COGSilo : public Component
{
public:
	COGSilo(exEngineInterface* pEngine, GameObject* pGameObject, int iNumberOfMissiles);
	~COGSilo();

	virtual ComponentType GetType() const override;
	virtual void Initialize() override;
	virtual void Destroy() override;
	void FireMissile(exVector2& target);
	void Update();
	bool CanFire();

	static std::vector<COGSilo*> mSiloComponents;
private:
	int mMissilesLeft;
	GameObjectManager* mGameObjectManager;
	exEngineInterface* mEngine;
	COGTransform* mTransformComponent;
	COGTextRenderer* mTextComponent;
	exColor mMissileColor;
};