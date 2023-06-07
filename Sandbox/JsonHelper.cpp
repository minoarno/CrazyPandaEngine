#include "MiniginPCH.h"
#include "JsonHelper.h"

#include <iostream>
#include "ResourceManager.h"
#include <fstream>

#include "GameObject.h"

#include "PrefabFactoryClass.h"
#include "HighScoreComponent.h"

void JsonHelper::LoadSceneUsingJson(const std::string& jsonFile, dae::GameObject* pLevelObject)
{
	auto posLevel = pLevelObject->GetComponent<dae::Transform>()->GetLocalPosition();

	nlohmann::json j = LoadJsonFile(jsonFile);

	dae::Scene* pScene = pLevelObject->GetScene();

	auto level = j.at("Level").get<std::vector<std::vector<int>>>();
	int blockWidth = j.at("BlockWidth").get<int>();
	int blockHeight = j.at("BlockHeight").get<int>();

	for (int r = 0; r < int(level.size()); r++)
	{
		for (int c = 0; c < int(level[r].size()); c++)
		{
			LevelBlockID id = LevelBlockID(level[r][c]);
			if (id != LevelBlockID::empty)
			{
				dae::GameObject* pLevelBlock = pLevelObject->AddChild(CreateBlock(*pScene,glm::vec2{c * blockWidth, r * blockHeight }, glm::vec2{ blockWidth,blockHeight }));
				pLevelBlock->SetTag("Level");
			}
		}
	}
}

nlohmann::json JsonHelper::LoadJsonFile(const std::string& jsonFile)
{
	std::ifstream inputFile{ dae::ResourceManager::GetInstance().GetDataPath() + jsonFile };

	nlohmann::json j;
	inputFile >> j;
	return j;
}

void JsonHelper::LoadHighScore(const std::string& /*jsonFile*/, HighScoreComponent* /*pHighScoreList*/)
{
}
