#include "COGArmory.h"

COGArmory::COGArmory(GameObject* pGameObject)
	:Component(pGameObject)
{

}

COGArmory::~COGArmory()
{
	Destroy();
}

void COGArmory::Destroy()
{
	mGameObject->RemoveComponent(this);
	Console::LogString("Deleted Armory Component! \n");
}

ComponentType COGArmory::GetType() const
{
	return ComponentType::Armory;
}

void COGArmory::RegisterSilo(int iSiloNumber, COGSilo* pSilo)
{
	mSilos.push_back(pSilo);
}

void COGArmory::FireFromSilo1(exVector2& position)
{
	// Fire missile with its target set to 
	mSilos[0]->FireMissile(position);
}

void COGArmory::FireFromSilo2(exVector2& position)
{
	// Fire missile with its target set to 
	mSilos[1]->FireMissile(position);
}

void COGArmory::FireFromSilo3(exVector2& position)
{
	// Fire missile with its target set to
	mSilos[2]->FireMissile(position);
}

bool COGArmory::SilosOutOfMissiles()
{
	for (COGSilo* pSilo : mSilos)
	{
		if (pSilo->CanFire())
		{
			return false;
		}
		
	}
	return true;
}