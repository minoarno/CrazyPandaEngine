#pragma once

namespace spdlog
{
	class logger;
}

class Log
{
public:
	static void Initialize();

	static void Trace(const std::string& message);
	static void Info(const std::string& message);
	static void Warning(const std::string& message);
	static void Error(const std::string& message);

	static void CoreTrace(const std::string& message);
	static void CoreInfo(const std::string& message);
	static void CoreWarning(const std::string& message);
	static void CoreError(const std::string& message);
private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
};