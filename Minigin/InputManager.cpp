#include "MiniginPCH.h"
#include "InputManager.h"
#include <XInput.h>
#include <Windows.h>
#include "Command.h"
#include <map>
#include <algorithm>
#include "SceneManager.h"
#include "Button.h"

struct InputStruct
{
public:
	Command* pOnPressDown = nullptr;
	Command* pOnHold = nullptr;
	Command* pOnRelease = nullptr;
	bool wasPressedDownPreviousFrame = false;

	InputStruct() = default;;
	~InputStruct() 
	{
		delete pOnPressDown;
		pOnPressDown = nullptr;

		delete pOnHold;
		pOnHold = nullptr;

		delete pOnRelease;
		pOnRelease = nullptr;
	}
};

struct PlayerButton
{
	ControllerButton button;
	DWORD playerID;
};
bool operator==(const PlayerButton& lhs, const PlayerButton& rhs)
{
	return lhs.button == rhs.button && lhs.playerID == rhs.playerID;
}
bool operator<(const PlayerButton& lhs, const PlayerButton& rhs)
{
	return lhs.button < rhs.button || (lhs.button == rhs.button && lhs.playerID < rhs.playerID);
}
bool operator>(const PlayerButton& lhs, const PlayerButton& rhs)
{
	return lhs.button > rhs.button || (lhs.button == rhs.button && lhs.playerID > rhs.playerID);
}

class InputManager::XInputManager final
{
public:
	XInputManager() = default;
	~XInputManager() = default;
	bool ProcessInput();
	[[nodiscard]] bool IsPressed(ControllerButton button, DWORD playerID) const;

	void AddOnPressDown(ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnHold(ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnRelease(ControllerButton controllerButton, Command* command, DWORD playerID = 0);

	void AddOnPressDown(SDL_Keycode keyButton, Command* command);
	void AddOnHold(SDL_Keycode keyButton, Command* command);
	void AddOnRelease(SDL_Keycode keyButton, Command* command);

	void AddUIButton(Button* pButton);

	void CleanUp();
private:
	std::map<PlayerButton, InputStruct*> m_ControllerCommands = std::map<PlayerButton, InputStruct*>();
	std::map<SDL_Keycode, InputStruct*> m_KeyboardCommands = std::map<SDL_Keycode, InputStruct*>();

	std::vector<Button*> m_pButtons{};

	bool m_DidInputGet = false;
};

bool InputManager::XInputManager::ProcessInput()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE m_pCurrentState{};

		ZeroMemory(&m_pCurrentState, sizeof(XINPUT_STATE));
		XInputGetState(i, &m_pCurrentState);

		if (IsPressed(static_cast<ControllerButton>(m_pCurrentState.Gamepad.wButtons), i))
		{
			m_ControllerCommands[PlayerButton{ static_cast<ControllerButton>(m_pCurrentState.Gamepad.wButtons), i }]->wasPressedDownPreviousFrame = true;
		}
		else
		{
			for (auto& c : m_ControllerCommands)
			{
				if (c.second->wasPressedDownPreviousFrame == true)
				{
					c.second->wasPressedDownPreviousFrame = false;
					if (c.second->pOnRelease != nullptr)
					{
						c.second->pOnRelease->Execute();			
					}
				}
			}
		}
	}


	std::vector<SDL_Keycode> keysPressedThisFrame = std::vector<SDL_Keycode>();
	//Makes us able to close the application
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		SDL_Keycode button = e.key.keysym.sym;
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			if (m_KeyboardCommands.contains(button))
			{
				auto command = m_KeyboardCommands[button];
				if (command->wasPressedDownPreviousFrame)
				{
					if (command->pOnHold != nullptr)
					{
						command->pOnHold->Execute();
					}
				}
				else
				{
					if (command->pOnPressDown != nullptr)
					{
						command->pOnPressDown->Execute();
					}
				}
				command->wasPressedDownPreviousFrame = true;
				keysPressedThisFrame.emplace_back(button);
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			if (m_KeyboardCommands.contains(button))
			{
				const auto& command = m_KeyboardCommands[button]; 
				if (command->pOnRelease != nullptr)
				{
					command->pOnRelease->Execute();
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			auto& activeScene = dae::SceneManager::GetInstance().GetActiveScene();
			for (size_t i = 0; i < m_pButtons.size(); i++)
			{
				if (m_pButtons[i]->GetGameObject()->GetScene()->GetSceneName() == activeScene.GetSceneName())
				{
					m_pButtons[i]->Click(glm::vec2{ e.motion.x,e.motion.y });
				}
			}
		}
	}

	for (auto& c : m_KeyboardCommands)
	{
		if (std::find(keysPressedThisFrame.begin(), keysPressedThisFrame.end(),c.first) == keysPressedThisFrame.end())
		{
			c.second->wasPressedDownPreviousFrame = false;
			if (c.second->pOnRelease != nullptr)
			{
				c.second->pOnRelease->Execute();
			}
		}
	}

	return true;
}

bool InputManager::XInputManager::IsPressed(ControllerButton button, DWORD playerID) const
{
	if (m_ControllerCommands.contains(PlayerButton{ button,playerID }))
	{
		if (m_ControllerCommands.at(PlayerButton{ button,playerID })->wasPressedDownPreviousFrame)
		{
			if (m_ControllerCommands.at(PlayerButton{ button,playerID })->pOnHold != nullptr)
			{
				m_ControllerCommands.at(PlayerButton{ button,playerID })->pOnHold->Execute();
			}
		}
		else
		{
			if (m_ControllerCommands.at(PlayerButton{ button,playerID })->pOnPressDown != nullptr)
			{
				m_ControllerCommands.at(PlayerButton{ button,playerID })->pOnPressDown->Execute();
			}
		}
		return true;
	}
	return false;
}

void InputManager::XInputManager::AddOnPressDown(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	auto button = PlayerButton{ controllerButton,playerID };
	if (!m_ControllerCommands.contains(button))
	{
		auto inputStruct = new InputStruct{};
		inputStruct->pOnPressDown = command;
		m_ControllerCommands.emplace(button, inputStruct);
	}
	else
	{
		m_ControllerCommands[button]->pOnPressDown = command;
	}
}

void InputManager::XInputManager::AddOnHold(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	auto button = PlayerButton{ controllerButton,playerID };
	if (!m_ControllerCommands.contains(PlayerButton{ controllerButton,playerID }))
	{
		auto* inputStruct = new InputStruct{};
		inputStruct->pOnHold = command;
		m_ControllerCommands.emplace(button, inputStruct);
	}
	else
	{
		m_ControllerCommands[button]->pOnHold = command;
	}
}

void InputManager::XInputManager::AddOnRelease(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	auto button = PlayerButton{ controllerButton,playerID };
	if (!m_ControllerCommands.contains(PlayerButton{ controllerButton,playerID }))
	{
		auto* inputStruct = new InputStruct{};
		inputStruct->pOnRelease = command;
		m_ControllerCommands.emplace(button, inputStruct);
	}
	else
	{
		m_ControllerCommands[button]->pOnRelease = command;
	}
}

void InputManager::XInputManager::AddOnPressDown(SDL_Keycode button, Command* command)
{
	if (!m_KeyboardCommands.contains(button))
	{
		auto* inputStruct = new InputStruct{};
		inputStruct->pOnPressDown = command;
		m_KeyboardCommands.emplace(button, inputStruct);
	}
	else
	{
		m_KeyboardCommands[button]->pOnPressDown = command;
	}
}

void InputManager::XInputManager::AddOnHold(SDL_Keycode button, Command* command)
{
	if (!m_KeyboardCommands.contains(button))
	{
		auto* inputStruct = new InputStruct{};
		inputStruct->pOnHold = command;
		m_KeyboardCommands.emplace(button, inputStruct);
	}
	else
	{
		m_KeyboardCommands[button]->pOnHold = command;
	}
}

void InputManager::XInputManager::AddOnRelease(SDL_Keycode button, Command* command)
{
	if (!m_KeyboardCommands.contains(button))
	{
		auto* inputStruct = new InputStruct{};
		inputStruct->pOnRelease = command;
		m_KeyboardCommands.emplace(button, inputStruct);
	}
	else
	{
		m_KeyboardCommands[button]->pOnRelease = command;
	}
}

void InputManager::XInputManager::AddUIButton(Button* pButton)
{
	m_pButtons.emplace_back(pButton);
}

void InputManager::XInputManager::CleanUp()
{
	for (auto& p : m_ControllerCommands)
	{
		delete p.second;
		p.second = nullptr;
	}
	m_ControllerCommands.clear();

	for (auto& p : m_KeyboardCommands)
	{
		delete p.second;
		p.second = nullptr;
	}
	m_KeyboardCommands.clear();
}

InputManager::InputManager()
	:pimpl{ std::make_unique<XInputManager>() }
{
}

InputManager::~InputManager() = default;

bool InputManager::ProcessInput() const
{
	return pimpl->ProcessInput();
}

bool InputManager::IsPressed(ControllerButton button, DWORD playerID) const
{
	return pimpl->IsPressed(button, playerID);
}

void InputManager::AddOnPressDown(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	pimpl->AddOnPressDown(controllerButton, command, playerID);
}

void InputManager::AddOnHold(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	pimpl->AddOnHold(controllerButton, command, playerID);
}

void InputManager::AddOnRelease(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	pimpl->AddOnRelease(controllerButton, command, playerID);
}

void InputManager::AddOnPressDown(SDL_Keycode keyButton, Command* command)
{
	pimpl->AddOnPressDown(keyButton, command);
}

void InputManager::AddOnHold(SDL_Keycode keyButton, Command* command)
{
	pimpl->AddOnHold(keyButton, command);
}

void InputManager::AddOnRelease(SDL_Keycode keyButton, Command* command)
{
	pimpl->AddOnRelease(keyButton, command);
}

void InputManager::AddUIButton(Button* pButton)
{
	pimpl->AddUIButton(pButton);
}

void InputManager::CleanUp()
{
	pimpl->CleanUp();
}