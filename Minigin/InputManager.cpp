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
	[[nodiscard]] bool IsPressed(int index, ControllerButton button, DWORD playerID) const;

	void AddOnPressDown(int index, ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnHold(int index, ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnRelease(int index, ControllerButton controllerButton, Command* command, DWORD playerID = 0);

	void AddOnPressDown(int index, SDL_Keycode keyButton, Command* command);
	void AddOnHold(int index, SDL_Keycode keyButton, Command* command);
	void AddOnRelease(int index, SDL_Keycode keyButton, Command* command);

	void AddUIButton(int index, Button* pButton);

	void CleanUp();
private:
	std::map<int, std::map<PlayerButton, InputStruct*>> m_ControllerCommands = std::map<int, std::map<PlayerButton, InputStruct*>>();
	std::map<int, std::map<SDL_Keycode, InputStruct*>> m_KeyboardCommands = std::map<int, std::map<SDL_Keycode, InputStruct*>>();

	std::map<int, std::vector<Button*>> m_pButtons{};

	bool m_DidInputGet = false;
};

bool InputManager::XInputManager::ProcessInput()
{
	int sceneIndex = dae::SceneManager::GetInstance().GetActiveSceneIndex();

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE m_pCurrentState{};

		ZeroMemory(&m_pCurrentState, sizeof(XINPUT_STATE));
		XInputGetState(i, &m_pCurrentState);

		if (IsPressed(sceneIndex, static_cast<ControllerButton>(m_pCurrentState.Gamepad.wButtons), i))
		{
			m_ControllerCommands[sceneIndex][PlayerButton{ static_cast<ControllerButton>(m_pCurrentState.Gamepad.wButtons), i }]->wasPressedDownPreviousFrame = true;
		}
		else
		{
			for (auto& c : m_ControllerCommands[sceneIndex])
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
			if (m_KeyboardCommands.contains(sceneIndex))
			{
				if (m_KeyboardCommands[sceneIndex].contains(button))
				{
					auto command = m_KeyboardCommands[sceneIndex][button];
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
		}
		else if (e.type == SDL_KEYUP)
		{
			if (m_KeyboardCommands.contains(sceneIndex))
			{
				if (m_KeyboardCommands[sceneIndex].contains(button))
				{
					const auto& command = m_KeyboardCommands[sceneIndex][button];
					if (command->pOnRelease != nullptr)
					{
						command->pOnRelease->Execute();
					}
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (m_pButtons.contains(sceneIndex))
			{
				for (size_t i = 0; i < m_pButtons[sceneIndex].size(); i++)
				{
					m_pButtons[sceneIndex][i]->Click(glm::vec2{ e.motion.x,e.motion.y });
				}
			}
		}
	}

	for (auto& c : m_KeyboardCommands[sceneIndex])
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

bool InputManager::XInputManager::IsPressed(int sceneIndex, ControllerButton button, DWORD playerID) const
{
	if (!m_ControllerCommands.contains(sceneIndex)) return false;
	
	if (!m_ControllerCommands.at(sceneIndex).contains(PlayerButton{button,playerID})) return false;

	if (m_ControllerCommands.at(sceneIndex).at(PlayerButton{ button,playerID })->wasPressedDownPreviousFrame)
	{
		if (m_ControllerCommands.at(sceneIndex).at(PlayerButton{ button,playerID })->pOnHold != nullptr)
		{
			m_ControllerCommands.at(sceneIndex).at(PlayerButton{ button,playerID })->pOnHold->Execute();
		}
	}
	else
	{
		if (m_ControllerCommands.at(sceneIndex).at(PlayerButton{ button,playerID })->pOnPressDown != nullptr)
		{
			m_ControllerCommands.at(sceneIndex).at(PlayerButton{ button,playerID })->pOnPressDown->Execute();
		}
	}
	return true;
}

void InputManager::XInputManager::AddOnPressDown(int sceneIndex, ControllerButton controllerButton, Command* command, DWORD playerID)
{
	if (!m_ControllerCommands.contains(sceneIndex))
	{
		m_ControllerCommands.emplace(sceneIndex, std::map<PlayerButton, InputStruct*>{});
	}

	auto button = PlayerButton{ controllerButton,playerID };
	if (!m_ControllerCommands.at(sceneIndex).contains(button))
	{
		auto inputStruct = new InputStruct{};
		m_ControllerCommands.at(sceneIndex).emplace(button, inputStruct);
	}

	m_ControllerCommands[sceneIndex][button]->pOnPressDown = command;
}

void InputManager::XInputManager::AddOnHold(int sceneIndex, ControllerButton controllerButton, Command* command, DWORD playerID)
{
	if (!m_ControllerCommands.contains(sceneIndex))
	{
		m_ControllerCommands.emplace(sceneIndex, std::map<PlayerButton, InputStruct*>{});
	}

	auto button = PlayerButton{ controllerButton,playerID };
	if (!m_ControllerCommands.at(sceneIndex).contains(PlayerButton{controllerButton,playerID}))
	{
		auto* inputStruct = new InputStruct{};
		m_ControllerCommands.at(sceneIndex).emplace(button, inputStruct);
	}

	m_ControllerCommands.at(sceneIndex)[button]->pOnHold = command;
}

void InputManager::XInputManager::AddOnRelease(int sceneIndex, ControllerButton controllerButton, Command* command, DWORD playerID)
{
	if (!m_ControllerCommands.contains(sceneIndex))
	{
		m_ControllerCommands.emplace(sceneIndex, std::map<PlayerButton, InputStruct*>{});
	}

	auto button = PlayerButton{ controllerButton,playerID };
	if (!m_ControllerCommands.at(sceneIndex).contains(PlayerButton{ controllerButton,playerID }))
	{
		auto* inputStruct = new InputStruct{};
		m_ControllerCommands.at(sceneIndex).emplace(button, inputStruct);
	}

	m_ControllerCommands[sceneIndex][button]->pOnRelease = command;
}

void InputManager::XInputManager::AddOnPressDown(int sceneIndex, SDL_Keycode button, Command* command)
{
	if (!m_KeyboardCommands.contains(sceneIndex))
	{
		m_KeyboardCommands.emplace(sceneIndex, std::map<SDL_Keycode, InputStruct*>{});
	}

	if (!m_KeyboardCommands.at(sceneIndex).contains(button))
	{
		auto* inputStruct = new InputStruct{};
		m_KeyboardCommands.at(sceneIndex).emplace(button, inputStruct);
	}

	m_KeyboardCommands[sceneIndex][button]->pOnPressDown = command;
}

void InputManager::XInputManager::AddOnHold(int sceneIndex, SDL_Keycode button, Command* command)
{
	if (!m_KeyboardCommands.contains(sceneIndex))
	{
		m_KeyboardCommands.emplace(sceneIndex, std::map<SDL_Keycode, InputStruct*>{});
	}

	if (!m_KeyboardCommands.at(sceneIndex).contains(button))
	{
		auto* inputStruct = new InputStruct{};
		m_KeyboardCommands.at(sceneIndex).emplace(button, inputStruct);
	}

	m_KeyboardCommands[sceneIndex][button]->pOnHold = command;
}

void InputManager::XInputManager::AddOnRelease(int sceneIndex, SDL_Keycode button, Command* command)
{
	if (!m_KeyboardCommands.contains(sceneIndex))
	{
		m_KeyboardCommands.emplace(sceneIndex, std::map<SDL_Keycode, InputStruct*>{});
	}

	if (!m_KeyboardCommands.at(sceneIndex).contains(button))
	{
		auto* inputStruct = new InputStruct{};
		m_KeyboardCommands.at(sceneIndex).emplace(button, inputStruct);
	}

	m_KeyboardCommands[sceneIndex][button]->pOnRelease = command;
}

void InputManager::XInputManager::AddUIButton(int sceneIndex, Button* pButton)
{
	if (!m_pButtons.contains(sceneIndex))
	{
		m_pButtons.emplace(sceneIndex, std::vector<Button*>{});
	}
	m_pButtons[sceneIndex].emplace_back(pButton);
}

void InputManager::XInputManager::CleanUp()
{
	for (auto& perScene : m_ControllerCommands)
	{
		for (auto& p : perScene.second)
		{
			delete p.second;
			p.second = nullptr;
		}
	}
	m_ControllerCommands.clear();

	for (auto& perScene : m_KeyboardCommands)
	{
		for (auto& p : perScene.second)
		{
			delete p.second;
			p.second = nullptr;
		}
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

bool InputManager::IsPressed(int index, ControllerButton button, DWORD playerID) const
{
	return pimpl->IsPressed(index, button, playerID);
}

void InputManager::AddOnPressDown(int index, ControllerButton controllerButton, Command* command, DWORD playerID)
{
	pimpl->AddOnPressDown(index, controllerButton, command, playerID);
}

void InputManager::AddOnHold(int index, ControllerButton controllerButton, Command* command, DWORD playerID)
{
	pimpl->AddOnHold(index, controllerButton, command, playerID);
}

void InputManager::AddOnRelease(int index, ControllerButton controllerButton, Command* command, DWORD playerID)
{
	pimpl->AddOnRelease(index, controllerButton, command, playerID);
}

void InputManager::AddOnPressDown(int index, SDL_Keycode keyButton, Command* command)
{
	pimpl->AddOnPressDown(index, keyButton, command);
}

void InputManager::AddOnHold(int index, SDL_Keycode keyButton, Command* command)
{
	pimpl->AddOnHold(index, keyButton, command);
}

void InputManager::AddOnRelease(int index, SDL_Keycode keyButton, Command* command)
{
	pimpl->AddOnRelease(index, keyButton, command);
}

void InputManager::AddUIButton(int index, Button* pButton)
{
	pimpl->AddUIButton(index, pButton);
}

void InputManager::CleanUp()
{
	pimpl->CleanUp();
}