#pragma once
#include "MiniginPCH.h"
#include "Log.h"
#pragma warning(push)
#pragma warning(disable : 26812)
#include "spdlog/sinks/stdout_color_sinks.h"

namespace dae
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger{};
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger{};

	void Log::Initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("MINIGIN CORE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
#pragma warning(pop)