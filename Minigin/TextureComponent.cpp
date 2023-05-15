#include "MiniginPCH.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(const std::string& filepath, int amountOfCols, int amountOfRows)
	: BaseComponent{}
	, m_pTexture{nullptr}
	, m_AmountOfRows{amountOfRows}
	, m_AmountOfCols{amountOfCols}
{
	SetTexture(filepath);
}

dae::TextureComponent::TextureComponent(SDL_Texture* pTexture, int amountOfCols, int amountOfRows)
	: BaseComponent{}
	, m_pTexture{ new Texture2D{pTexture} }
	, m_AmountOfRows{ amountOfRows }
	, m_AmountOfCols{ amountOfCols }
	, m_IsInChargeOfDeletion{ true }
{
	CalculateDimension();
}

dae::TextureComponent::~TextureComponent()
{
	if (m_IsInChargeOfDeletion)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	CalculateDimension();
	CalculateSourceRect(0);
}

void dae::TextureComponent::SetDestinationRectDimensions(const glm::vec2& dst)
{
	m_DestinationRect.w = dst.x;
	m_DestinationRect.h = dst.y;
}

Rectf dae::TextureComponent::GetDestinationRect() const
{
	const glm::vec3 pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
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
	const int colIndex{ imagePartIndex % m_AmountOfCols };
	const int rowIndex{ imagePartIndex / m_AmountOfCols };

	CalculateSourceRect(colIndex, rowIndex);
}

void dae::TextureComponent::CalculateSourceRect(int col, int row)
{
	const float widthPart{ static_cast<float>(m_Width) / static_cast<float>(m_AmountOfCols) };
	const float heightPart{ static_cast<float>(m_Height) / static_cast<float>(m_AmountOfRows) };

	m_SourceRect = Rectf{static_cast<float>(col) * widthPart,static_cast<float>(row) * heightPart,widthPart,heightPart };
}

void dae::TextureComponent::Render() const
{
	if (m_pGameObject == nullptr)return;

	const Transform* pTransform = m_pGameObject->GetTransform();
	const glm::vec3 pos = pTransform->GetWorldPosition();

	const Rectf dstRect = GetDestinationRect();
	const Rectf srcRect = GetSourceRect();

	const SDL_Rect dst = { static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(dstRect.w), static_cast<int>(dstRect.h) };
	const SDL_Rect src = { static_cast<int>(srcRect.x),static_cast<int>(srcRect.y),static_cast<int>(srcRect.w),static_cast<int>(srcRect.h) };

	if(src.w != 0 && src.h != 0)
	{
		if (dst.w != 0 && dst.h != 0)
		{
			Renderer::GetInstance().RenderTexture(this, src, dst);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(this, src, dst.x, dst.y)	;
		}
	}
	else
	{
		Renderer::GetInstance().RenderTexture(this,static_cast<const float>(dst.x),static_cast<const float>(dst.y));
	}
}

void dae::TextureComponent::UpdateTexture()
{
	CalculateDimension();
}

void dae::TextureComponent::CalculateDimension()
{
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_Width, &m_Height);
}
