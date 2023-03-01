#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"
#include "TextureComponent.h"
#include "Transform.h"
#include "ResourceManager.h" 

dae::TextComponent::TextComponent(dae::Font* font, const std::string& text)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(font)
{
}

void dae::TextComponent::LateUpdate()
{
	if (m_NeedsUpdate)
	{
		if (m_Text != "" && m_Font != nullptr)
		{
			SDL_Surface* surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
			if (surf == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			
			SDL_Texture* texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);

			if (m_pGameObject != nullptr)
			{
				if (m_pGameObject->GetComponent<TextureComponent>() == nullptr)
				{
					m_pGameObject->AddComponent(new TextureComponent{ texture });
				}
				else
				{
					m_pGameObject->SetComponent<TextureComponent>(new TextureComponent{ texture });
				}
			}
		}
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_Text != "")
	{
		const glm::vec3 pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
		if (m_pGameObject->GetComponent<TextureComponent>() != nullptr)
		{
			dae::Renderer::GetInstance().RenderTexture(m_pGameObject->GetComponent<TextureComponent>(), pos.x, pos.y);
		}
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const Colorf color)
{
	m_Color = { static_cast<unsigned char>(color.r), static_cast<unsigned char>(color.g), static_cast<unsigned char>(color.b) };
}
