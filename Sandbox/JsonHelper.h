#pragma once
#pragma once
#pragma warning(push)
#pragma warning(disable : 26800)
#include "json.hpp"
#pragma warning(pop)

class HighScoreComponent;
namespace dae
{
	class GameObject;
}

enum class LevelBlockID
{
	empty = 0,
	block = 1
};

namespace JsonHelper
{
	void LoadSceneUsingJson(const std::string& jsonFile, dae::GameObject* pLevelObject);
	nlohmann::json LoadJsonFile(const std::string& jsonFile);
	void LoadHighScore(const std::string& jsonFile, HighScoreComponent* pHighScoreList);
};

