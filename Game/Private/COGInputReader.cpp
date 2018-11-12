 #include "COGInputReader.h"
 #include "GameObject.h"
#include "Engine\Public\SDL.h"
#include "Output.h"
#include <algorithm>

std::vector<COGPlayerInputReader*> COGPlayerInputReader::mInputReaderComponents;

COGPlayerInputReader::COGPlayerInputReader(GameObject* pGameObject)
	:Component(pGameObject)
{
	mInputReaderComponents.push_back(this);

	InputManager* pInputManager = InputManager::GetInstance();
	mInputState = pInputManager->GetInputState();
}

COGPlayerInputReader::~COGPlayerInputReader()
{
	Destroy();
}

void COGPlayerInputReader::Destroy()
{
	// Removing the component from the static vector
	mInputReaderComponents.erase(std::remove(mInputReaderComponents.begin(), mInputReaderComponents.end(), this), mInputReaderComponents.end());

	// Removing the component from the component list
	mGameObject->RemoveComponent(this);
	Console::LogString("Deleted Input Component! \n");
}

void COGPlayerInputReader::Initialize()
{
	mTransform = mGameObject->FindComponent<COGTransform>(ComponentType::Transform);
	mArmory = mGameObject->FindComponent<COGArmory>(ComponentType::Armory);
}

void COGPlayerInputReader::Update()
{
	// Moving the cursor to the mouse position
	exVector2& position = mTransform->GetPosition();
	position = mInputState->GetMousePosition();

	// Checking for other inputs from the player

	if (mInputState->PressedSilo1())
	{
		//Console::LogString("Target : X - " + std::to_string(position.x) + " Y - " + std::to_string(position.y) + "\n");
		mArmory->FireFromSilo1(position);
	}

	if (mInputState->PressedSilo2())
	{
		mArmory->FireFromSilo2(position);
	}

	if (mInputState->PressedSilo3())
	{
		mArmory->FireFromSilo3(position);
	}
}

ComponentType COGPlayerInputReader::GetType() const
{
	return ComponentType::InputReader;
}