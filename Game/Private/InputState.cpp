#include "InputState.h"
#include <iostream>

InputState::InputState()
{
	mState = 0;
	mPreviousState = 0;
}

InputState::~InputState()
{
	// Nothing to destruct for now
}

bool InputState::PressedSilo1() const
{
	// Checks if the key has been just pressed
	return ((mState & INPUT_SILO_1) != 0 && (mPreviousState & INPUT_SILO_1) == 0);
}

bool InputState::PressedSilo2() const
{
	// Checks if the key has been just pressed
	return ((mState & INPUT_SILO_2) != 0 && (mPreviousState & INPUT_SILO_2) == 0);
}

bool InputState::PressedSilo3() const
{
	// Checks if the key has been just pressed
	return ((mState & INPUT_SILO_3) != 0 && (mPreviousState & INPUT_SILO_3) == 0);
}

bool InputState::PressedDebug() const
{
	return ((mState & INPUT_DEBUG) != 0 && (mPreviousState & INPUT_DEBUG) == 0);
}

exVector2 InputState::GetMousePosition()
{
	// Sending the mouse position as a exVector2-float
	return {float(mMouseState.x), float(mMouseState.y)};
}