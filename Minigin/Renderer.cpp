#include "MiniginPCH.h"
#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "TextureComponent.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();
	
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	//ImGui::ShowDemoWindow();

	int xValues[11]{ 0,1,2,3,4,5,6,7,8,9,10 };
	const char* const xValuesText[11]{ "1","2","4","8","16","32","64","128","256","512","1024" };
	int yValues1[11]{ 8585,8143,5343,3222,1712,590,131,134,38,14,7};
	int yValues2[11]{ 6239,3452,2456,2291,2272,975,654,313,160,70,13 };

	if (ImPlot::BeginPlot("Trash The Cache"))
	{
		ImPlot::SetupAxes("stepsize", "avg. time (in ms)", ImPlotAxisFlags_::ImPlotAxisFlags_PanStretch);
		ImPlot::PlotLine("avg.time", xValues, yValues1, 11);
		ImPlot::PlotLine("avg. time Alt", xValues, yValues2, 11);
		ImPlot::SetupAxisLimitsConstraints(ImAxis_::ImAxis_X1, 0, 9000);

		ImPlot::EndPlot();
	}

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	if (m_renderer != nullptr)
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImPlot::DestroyContext();
		ImGui::DestroyContext();

		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const dae::TextureComponent* pTextureComponent, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(pTextureComponent->GetTexture()->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), pTextureComponent->GetTexture()->GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const dae::TextureComponent* pTextureComponent, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), pTextureComponent->GetTexture()->GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const TextureComponent* pTextureComponent, const SDL_Rect& srcRect, const int x, const int y) const
{
	RenderTexture(pTextureComponent, srcRect, x, y, pTextureComponent->GetTextureWidth(), pTextureComponent->GetTextureHeight());
}

void dae::Renderer::RenderTexture(const TextureComponent* pTextureComponent, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), pTextureComponent->GetTexture()->GetSDLTexture(), &srcRect, &dstRect);
}

void dae::Renderer::RenderTexture(const TextureComponent* pTextureComponent, const SDL_Rect& srcRect, const int x, const int y, const int width, const int height) const
{
	SDL_Rect dst{ x,y,width,height };
	RenderTexture(pTextureComponent,srcRect, dst);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
