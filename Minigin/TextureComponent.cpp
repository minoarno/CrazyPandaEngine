#pragma once
#include "MiniginPCH.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(const std::string& filepath, int amountOfCols, int amountOfRows)
	: dae::BaseComponent{}
	, m_AmountOfCols{amountOfCols}
	, m_AmountOfRows{amountOfRows}
	, m_IsInChargeOfDeletion{ false }
{
	SetTexture(filepath);
}

dae::TextureComponent::TextureComponent(SDL_Texture* pTexture, int amountOfCols, int amountOfRows)
	: dae::BaseComponent{}
	, m_pTexture{ std::make_shared<dae::Texture2D>(pTexture) }
	, m_IsInChargeOfDeletion{ true }
	, m_AmountOfCols{ amountOfCols }
	, m_AmountOfRows{ amountOfRows }
{
	CalculateDimension();
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	CalculateDimension();
	CalculateSourceRect(0);
}

void dae::TextureComponent::SetDestinationRectDimensions(const Vector2f& dst)
{
	m_DestinationRect.w = dst.x;
	m_DestinationRect.h = dst.y;
}

Rectf dae::TextureComponent::GetDestinationRect() const
{
	auto pos = m_pGameObject->GetPosition();
	return Rectf{ pos.x,pos.y ,m_DestinationRect.w,m_DestinationRect.h };
}

void dae::TextureComponent::SetSourceRect(const Rectf& src)
{
	m_SourceRect = src;
}

Rectf dae::TextureComponent::GetSourceRect() const
{
	return m_SourceRect;
}

void dae::TextureComponent::CalculateSourceRect(int imagePartIndex)
{
	int colIndex{ imagePartIndex % m_AmountOfCols };
	int rowIndex{ imagePartIndex / m_AmountOfCols };

	CalculateSourceRect(colIndex, rowIndex);
}

void dae::TextureComponent::CalculateSourceRect(int col, int row)
{
	float widthPart{ float(m_Width) / m_AmountOfCols };
	float heightPart{ float(m_Height) / m_AmountOfRows };

	m_SourceRect = Rectf{ col * widthPart,row * heightPart,widthPart,heightPart };
}

void dae::TextureComponent::UpdateTexture()
{
	CalculateDimension();
}

void dae::TextureComponent::Render() const
{

}

void dae::TextureComponent::CalculateDimension()
{
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_Width, &m_Height);
}
