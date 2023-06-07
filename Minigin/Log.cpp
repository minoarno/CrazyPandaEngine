#pragma once
#include "MiniginPCH.h"
#include "Log.h"
#pragma warning(push)
#pragma warning(disable : 26812)
#include "spdlog/sinks/stdout_color_sinks.h"

//Mentioned in the youtube video of The Cherno about Logging
//https://www.youtube.com/watch?v=dZr-53LAlOw&t=915s
//Installed from the github page
//https://github.com/gabime/spdlog

#include <memory>
#include "spdlog/spdlog.h"

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

void Log::Trace(const std::string& message)
{
	s_ClientLogger->trace(message);
}

void Log::Info(const std::string& message)
{
	s_ClientLogger->info(message);
}

void Log::Warning(const std::string& message)
{
	s_ClientLogger->warn(message);
}

void Log::Error(const std::string& message)
{
	s_ClientLogger->error(message);
}

void Log::CoreTrace(const std::string& message)
{
	s_CoreLogger->trace(message);
}

void Log::CoreInfo(const std::string& message)
{
	s_CoreLogger->info(message);
}

void Log::CoreWarning(const std::string& message)
{
	s_CoreLogger->warn(message);
}

void Log::CoreError(const std::string& message)
{
	s_CoreLogger->error(message);
}

#pragma warning(pop)