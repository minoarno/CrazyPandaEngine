#pragma once
#include <SDL.h>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class TextureComponent;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const dae::TextureComponent* pTextureComponent, const float x, const float y) const;
		void RenderTexture(const dae::TextureComponent* pTextureComponent, const float x, const float y, const float width, const float height) const;
		void RenderTexture(const TextureComponent* pTextureComponent, const SDL_Rect& srcRect, const int x, const int y) const;
		void RenderTexture(const TextureComponent* pTextureComponent, const SDL_Rect& srcRect, const int x, const int y, const int width, const int height) const;
		void RenderTexture(const TextureComponent* pTextureComponent, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

