#pragma once
#include "Component.h"
#include "COGSilo.h" 

class COGArmory : public Component
{
public:
	COGArmory(GameObject* pGameObject);
	~COGArmory();
	
	virtual ComponentType GetType() const override;
	virtual void Destroy() override;

	void RegisterSilo(int iSiloNumbers, COGSilo* silo);
	void FireFromSilo1(exVector2& position);
	void FireFromSilo2(exVector2& position);
	void FireFromSilo3(exVector2& position);
	bool SilosOutOfMissiles();

private:
	std::vector<COGSilo*> mSilos;
	COGSilo*				mSilo1;
	COGSilo*				mSilo2;
	COGSilo*				mSilo3;
};