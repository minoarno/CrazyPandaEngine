#pragma once
#include "Singleton.h"
#include <memory>

enum class ControllerButton
{
	DPadUp = 0x0001,
	DPadDown = 0x0002,
	DPadLeft = 0x0004,
	DPadRight = 0x0008,
	ButtonStart = 0x0010,
	ButtonBack = 0x0020,
	LeftThumb = 0x0040,
	RightThumb = 0x0080,
	LeftShoulder = 0x0100,
	RightShoulder = 0x0200,
	ButtonA = 0x1000,
	ButtonB = 0x2000,
	ButtonX = 0x4000,
	ButtonY = 0x8000
};

class Button;
class Command;
class InputManager final : public dae::Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

	bool ProcessInput() const;
	bool IsPressed(int index ,ControllerButton button, DWORD playerID) const;

	void AddOnPressDown(int index, ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnHold(int index, ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnRelease(int index, ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	
	void AddOnPressDown(int index, SDL_Keycode keyButton, Command* command);
	void AddOnHold(int index, SDL_Keycode keyButton, Command* command);
	void AddOnRelease(int index, SDL_Keycode keyButton, Command* command);

	void AddUIButton(int index, Button* pButton);

	void CleanUp();
private:
	class XInputManager;
	std::unique_ptr<XInputManager> pimpl{};
};