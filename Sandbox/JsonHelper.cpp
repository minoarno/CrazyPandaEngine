#include "MiniginPCH.h"
#include "JsonHelper.h"

#include <iostream>
#include "ResourceManager.h"
#include <fstream>

#include "PrefabFactoryClass.h"
#include "HighScoreComponent.h"

void JsonHelper::LoadSceneUsingJson(const std::string& jsonFile, dae::GameObject* pLevelObject)
{
	try
	{
		nlohmann::json j = LoadJsonFile(jsonFile);
		pLevelObject->GetTransform()->SetLocalPosition(20, 40, 0);
		auto posLevel = pLevelObject->GetComponent<dae::Transform>()->GetLocalPosition();

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
					auto pLevelBlock = CreateBlock(pLevelObject, glm::vec2{ c * blockWidth, r * blockHeight }, glm::vec2{ blockWidth,blockHeight}, (int)id);
					pLevelBlock->SetTag("Level");
				}
			}
		}

		//Border
		for (int r = -1; r <= int(level.size()); r++)
		{
			for (int c = -1; c <= int(level[0].size()); c++)
			{
				if (c == -1 || r == -1 || c == int(level[0].size()) || r == int(level.size()))
				{
					auto pLevelBlock = CreateBlock(pLevelObject, glm::vec2{ c * blockWidth, r * blockHeight }, glm::vec2{ blockWidth,blockHeight }, 0);
					pLevelBlock->SetTag("Border");
				}
			}
		}

		CreatePooka(*pLevelObject->GetScene(), glm::vec2{ posLevel.x + 4 * blockWidth, posLevel.y + 6 * blockHeight });
		CreatePooka(*pLevelObject->GetScene(), glm::vec2{ posLevel.x + 8 * blockWidth, posLevel.y + 8 * blockHeight });
	}
	catch (const std::exception&)
	{
	}
}

nlohmann::json JsonHelper::LoadJsonFile(const std::string& jsonFile)
{
	std::ifstream inputFile{ dae::ResourceManager::GetInstance().GetDataPath() + jsonFile };
	if (inputFile.fail())
	{
		Log::CoreWarning("File \"" + jsonFile + "\" can't be opened or found!");
		return nullptr;
	}

	nlohmann::json j;
	inputFile >> j;
	return j;
}

void JsonHelper::LoadHighScore(const std::string& jsonFile, HighScoreComponent* /*pHighScoreList*/)
{
	try
	{
		nlohmann::json j = LoadJsonFile(jsonFile);
	}
	catch (const std::exception&)
	{

	}
}

void JsonHelper::SaveHighScore(const std::string& jsonFile, HighScoreComponent* /*pHighScoreList*/)
{
	try
	{
		nlohmann::json j = LoadJsonFile(jsonFile);
	}
	catch (const std::exception&)
	{

	}
}
