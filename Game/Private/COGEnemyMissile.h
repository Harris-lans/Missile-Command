#pragma once
#include "COGLineShape.h"

class COGEnemyMissile : public Component
{
public:
	COGEnemyMissile(GameObject* pGameObject);
	~COGEnemyMissile();

	virtual void Destroy() override;
	void Update();
	virtual void Initialize() override;
	virtual ComponentType GetType() const override;

	static std::vector<COGEnemyMissile*> mEnemyMissiles;

private:
	COGTransform * mTransformComponent;
	COGLineShape* mMissileTrailComponent;
};