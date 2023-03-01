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
			const SDL_Color color = { 255,255,255 }; // only white text is supported now
			SDL_Surface* surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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
		auto pos = m_pGameObject->GetPosition();
		if (m_pGameObject->GetComponent<TextureComponent>() != nullptr)
		{
			dae::Renderer::GetInstance().RenderTexture(
				*m_pGameObject->GetComponent<TextureComponent>()->GetTexture(),
				pos.x, pos.y);
		}
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}