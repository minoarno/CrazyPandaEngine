#include "MiniginPCH.h"
#include "JsonHelper.h"

#include <iostream>
#include "ResourceManager.h"
#include <fstream>

#include "PrefabFactoryClass.h"
#include "HighScoreComponent.h"

#include "ScoreManager.h"

void JsonHelper::LoadSceneUsingJson(const std::string& jsonFile, dae::GameObject* pLevelObject)
{
	try
	{
		nlohmann::json j = LoadJsonFile(jsonFile);
		pLevelObject->GetTransform()->SetLocalPosition(45, 40, 0);
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

		auto enemies = j.at("Enemies");
		if (enemies.is_array()) {
			for (const auto& object : enemies) {
				int enemyType = object["Type"].get<int>();
				int rowIndex = object["Row"].get<int>();
				int colIndex = object["Col"].get<int>();

				switch (enemyType)
				{
				case 0:
				default:
					CreatePooka(*pLevelObject->GetScene(), glm::vec2{ posLevel.x + colIndex * blockWidth, posLevel.y + rowIndex * blockHeight });
					break;
				case 1:
					CreateFygar(*pLevelObject->GetScene(), glm::vec2{ posLevel.x + colIndex * blockWidth, posLevel.y + rowIndex * blockHeight });
					break;
				case 2:
					CreateRock(*pLevelObject->GetScene(), glm::vec2{posLevel.x + colIndex * blockWidth, posLevel.y + rowIndex * blockHeight});
					break;
				}
			}
		}

		auto heights = j.at("Heights").get<std::vector<float>>();
		ScoreManager::GetInstance().SetHeightLevels(heights);
	}
	catch (const std::exception&)
	{
		Log::Warning("There has been an issue while loading in the level.");
	}
}

nlohmann::json JsonHelper::LoadJsonFile(const std::string& jsonFile)
{
	std::ifstream inputFile{ dae::ResourceManager::GetInstance().GetDataPath() + jsonFile };
	if (inputFile.fail())
	{
		Log::Warning("File \"" + jsonFile + "\" can't be opened or found!");
		return nullptr;
	}

	nlohmann::json j;
	inputFile >> j;
	return j;
}

void JsonHelper::SaveJsonFile(const std::string& jsonFile, const nlohmann::json& json)
{
	std::ofstream outputFile{ dae::ResourceManager::GetInstance().GetDataPath() + jsonFile };

	outputFile << json;
	outputFile.close();
}

void JsonHelper::LoadHighScore(const std::string& jsonFile, HighScoreComponent* pHighScoreList)
{
	try
	{
		nlohmann::json highscoreList = LoadJsonFile(jsonFile);

		if (highscoreList.is_array()) {
			for (const auto& object : highscoreList) {
				int score = object["Score"].get<int>();

				pHighScoreList->AddScore(score);
			}
		}
	}
	catch (const std::exception&)
	{
		Log::Warning("There has been an issue while loading the highscore.");
	}
}

void JsonHelper::SaveHighScore(const std::string& jsonFile, HighScoreComponent* pHighScoreList)
{
	try
	{
		nlohmann::json j{};
		auto highscores = pHighScoreList->GetHighScores();
		for (auto s : highscores)
		{
			nlohmann::json score;
			score["Score"] = s;
			j.emplace_back(score);
		}
		SaveJsonFile(jsonFile, j);
	}
	catch (const std::exception&)
	{
		Log::Warning("There has been an issue while saving the highscore.");
	}
}
