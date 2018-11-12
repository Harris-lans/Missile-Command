#include "COGPhysics.h"
#include "COGLineShape.h"
#include "GameObjectManager.h"

class COGFriendlyMissile : public Component
{
public:
	COGFriendlyMissile(exEngineInterface* pEngine, GameObject* pGameObject, exVector2& targetPosition);
	~COGFriendlyMissile();

	virtual ComponentType GetType() const override;
	virtual void Initialize() override;
	virtual void Destroy() override;
	void Update();

	static std::vector<COGFriendlyMissile*> mFriendlyMissiles;
private:
	exEngineInterface *			mEngine;
	exVector2					mTargetPosition;
	COGPhysics*					mPhysicsComponent;
	COGTransform*				mTransformComponent;
	COGLineShape*				mMissileTrail;
	GameObjectManager*			mGameObjectManager;
	GameObjectHandle			mExplosionHandle;
	bool						mHasExploded;
};