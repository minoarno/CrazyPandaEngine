#include "MiniginPCH.h"
#include "Button.h"

#include "Command.h"
#include "InputManager.h"

Button::Button(const glm::vec2& dimensions, Command* pCommand)
	: BaseComponent{ }
	, m_pCommand{ pCommand }
	, m_Dimensions{ dimensions }
{
}

Button::~Button()
{
	delete m_pCommand;
	m_pCommand = nullptr;
}

Rectf Button::GetHitbox() const
{
	auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
	return Rectf(pos.x, pos.y, m_Dimensions.x, m_Dimensions.y);
}

void Button::Click(const glm::vec2& mousePos)
{
	if (IsOverlapping(GetHitbox(), mousePos))
	{
		m_pCommand->Execute();
	}
}

void Button::Initialize()
{
	InputManager::GetInstance().AddUIButton(m_pGameObject->GetScene()->GetIndex(), this);
}
