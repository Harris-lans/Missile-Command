#pragma once
#include "Engine\Public\EngineInterface.h"
#include "Engine\Public\EngineInterface.h"

enum States
{
	INPUT_SILO_1 = 1 << 0,
	INPUT_SILO_2 = 1 << 1,
	INPUT_SILO_3 = 1 << 2,
	INPUT_LMB = 1 << 3,
	INPUT_DEBUG = 1 << 4
};

enum class Devices
{
	MOUSE = 0,
	KEYBOARD
};

class InputState
{
private:
	int mState;
	int mPreviousState;
	exIntegerVector2 mMouseState;

public:
	friend class InputManager;

	InputState();
	~InputState();

	bool PressedSilo1() const;
	bool ReleasedSilo1() const;
	bool HoldingSilo1() const;

	bool PressedSilo2() const;
	bool ReleasedSilo2() const;
	bool HoldingSilo2() const;

	bool PressedSilo3() const;
	bool ReleasedSilo3() const;
	bool HoldingSilo3() const;

	bool PressedDebug() const;

	exVector2 GetMousePosition();
};