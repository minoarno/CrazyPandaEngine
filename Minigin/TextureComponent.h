#pragma once
#include "BaseComponent.h"

struct SDL_Texture;
namespace dae
{
	class Texture2D;
	class TextureComponent final: public BaseComponent
	{
	public:
		TextureComponent(const std::string& filepath, int amountOfCols = 1, int amountOfRows = 1);
		TextureComponent(SDL_Texture* pTexture, int amountOfCols = 1, int amountOfRows = 1);

		TextureComponent(const TextureComponent&) = delete;
		TextureComponent& operator=(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator=(TextureComponent&&) = delete;
		~TextureComponent() = default;

		void SetIsFlipped(bool value) { m_IsFlipped = value; }
		bool GetIsFlipped()const { return m_IsFlipped; }

		std::shared_ptr<Texture2D> GetTexture()const { return m_pTexture; }
		void SetTexture(const std::string& filename);

		void SetDestinationRectDimensions(const Vector2f& dst);
		Rectf GetDestinationRect()const;
		void SetSourceRect(const Rectf& src);
		Rectf GetSourceRect()const;

		void CalculateSourceRect(int imagePartIndex);
		void CalculateSourceRect(int col, int row);

		int GetTextureWidth()const { return m_Width; };
		int GetTextureHeight()const { return m_Height; };

		int GetImagePartWidth()const { return m_Width / m_AmountOfCols; };
		int GetImagePartHeight()const { return m_Height / m_AmountOfRows; };

		void UpdateTexture();
	protected:
		virtual void Render() const override;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		Rectf m_DestinationRect{};
		Rectf m_SourceRect{};

		int m_Width{};
		int m_Height{};

		int m_AmountOfRows{ 1 };
		int m_AmountOfCols{ 1 };

		bool m_IsFlipped{ false };
		bool m_IsInChargeOfDeletion{ false };

		void CalculateDimension();
	};
}


