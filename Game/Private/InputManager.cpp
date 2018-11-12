#include "InputManager.h"

InputManager::InputManager()
{
	inputState = new InputState();
}

InputManager::~InputManager()
{
	delete inputState;
	inputState = nullptr;
}

void InputManager::Update()
{
	// Storing the previous state before updating the current state
	inputState->mPreviousState = inputState->mState;

	inputState->mState = 0;

	SDL_GetMouseState(&(inputState->mMouseState.x), &(inputState->mMouseState.y));

	if (IsButtonDown(SDL_SCANCODE_A))
	{
		inputState->mState |= INPUT_SILO_1;
	}

	if (IsButtonDown(SDL_SCANCODE_S))
	{
		inputState->mState |= INPUT_SILO_2;
	}

	if (IsButtonDown(SDL_SCANCODE_D))
	{
		inputState->mState |= INPUT_SILO_3;
	}

	if (IsButtonDown(SDL_SCANCODE_L))
	{
		inputState->mState |= INPUT_DEBUG;
	}
}

bool InputManager::IsButtonDown(Uint8 nScancode) const
{
	int keys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &keys );
	return pState[nScancode];
}

/*bool InputManager::IsMouseButtonDown(Uint8 nScanCode)const
{
	const Uint32 State = SDL_GetMouseState(NULL, NULL);
	return State & SDL_BUTTON(nScanCode);
}*/

InputState* InputManager::GetInputState() const
{
	return inputState;
}