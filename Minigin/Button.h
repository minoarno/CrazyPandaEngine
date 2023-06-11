#pragma once
#include "BaseComponent.h"
#include <functional>
#include "HelperStructs.h"

class Command;
class Button : public dae::BaseComponent
{
public:
	Button(const glm::vec2& dimensions, Command* pCommand);
	Button(const Button& other) = delete;
	Button(Button&& other) = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) = delete;
	virtual ~Button();

	Rectf GetHitbox()const;
	void Click(const glm::vec2& mousePos);

private:
	Command* m_pCommand;

	glm::vec2 m_Dimensions{};
};

