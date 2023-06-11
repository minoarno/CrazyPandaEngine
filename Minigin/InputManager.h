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
	bool IsPressed(ControllerButton button, DWORD playerID) const;

	void AddOnPressDown(ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnHold(ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnRelease(ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	
	void AddOnPressDown(SDL_Keycode keyButton, Command* command);
	void AddOnHold(SDL_Keycode keyButton, Command* command);
	void AddOnRelease(SDL_Keycode keyButton, Command* command);

	void AddUIButton(Button* pButton);

	void CleanUp();
private:
	class XInputManager;
	std::unique_ptr<XInputManager> pimpl{};
};