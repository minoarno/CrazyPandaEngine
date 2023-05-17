#pragma once
//Mentioned in the youtube video of The Cherno about Logging
//https://www.youtube.com/watch?v=dZr-53LAlOw&t=915s
//Installed from the github page
//https://github.com/gabime/spdlog

#include <memory>
#include "spdlog/spdlog.h"

namespace dae
{
	class Log
	{
	public:
		static void Initialize();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define ME_CORE_TRACE(...) ::dae::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ME_CORE_INFO(...)  ::dae::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ME_CORE_WARN(...)  ::dae::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ME_CORE_ERROR(...) ::dae::Log::GetCoreLogger()->error(__VA_ARGS__)

//Client log macros
#define ME_TRACE(...)      ::dae::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ME_INFO(...)       ::dae::Log::GetClientLogger()->info(__VA_ARGS__)
#define ME_WARN(...)       ::dae::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ME_ERROR(...)      ::dae::Log::GetClientLogger()->error(__VA_ARGS__)