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
		void Render([[maybe_unused]] bool drawBox2DRenderer) const;
		void Destroy();

		void RenderTexture(const TextureComponent* pTextureComponent, float x, float y) const;
		void RenderTexture(const TextureComponent* pTextureComponent, float x, float y, float width, float height) const;
		void RenderTexture(const TextureComponent* pTextureComponent, const SDL_Rect& srcRect, int x, int y) const;
		void RenderTexture(const TextureComponent* pTextureComponent, const SDL_Rect& srcRect, int x, int y, int width, int height) const;
		void RenderTexture(const TextureComponent* pTextureComponent, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const;

		void DrawRectangle(const SDL_Rect& rect, const Colorf& color);

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

