#pragma once
#include "InputManager.h"
#include "COGTransform.h"
#include  "COGArmory.h"
#include "Component.h"

class COGPlayerInputReader : public Component
{
public:
	static std::vector<COGPlayerInputReader*> mInputReaderComponents;

public:
	COGPlayerInputReader(GameObject* pGameObject);
	~COGPlayerInputReader();

	ComponentType GetType() const;

	virtual void Update();

	virtual void Initialize() override;
	virtual void Destroy() override;

private:
	InputState* mInputState;
	COGTransform* mTransform;
	COGArmory* mArmory;
};