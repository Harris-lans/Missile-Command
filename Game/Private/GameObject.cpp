#include "GameObject.h"
#include <algorithm>

int GameObject::gameObjectNumber = rand() % 999;

GameObject::GameObject(Hash hash)
{
	mHash = hash;
	++gameObjectNumber;
}

GameObject::~GameObject()
{
	int numberOfComponents = mComponents.size();
	for (int i = 0; i < numberOfComponents; i++)
	{
		delete mComponents[0];
	}
}

void GameObject::Initialize()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);
}

void GameObject::RemoveComponent(Component* pComponent)
{
	mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), pComponent), mComponents.end());
}

int GameObject::NumberOfComponents() const
{
	return mComponents.size();
}

