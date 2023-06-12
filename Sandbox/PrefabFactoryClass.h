#pragma once
namespace dae
{
	class GameObject;
	class Scene;
}
class Command;

dae::GameObject* CreatePlayer(dae::Scene& scene, const glm::vec2& pos);
dae::GameObject* CreatePooka(dae::Scene& scene, const glm::vec2& pos);
dae::GameObject* CreateFygar(dae::Scene& scene, const glm::vec2& pos);
dae::GameObject* CreatePlayerFygar(dae::Scene& scene, const glm::vec2& pos);
dae::GameObject* CreateRock(dae::Scene& scene, const glm::vec2& pos);
dae::GameObject* CreateBlock(dae::GameObject* pLevel, const glm::vec2& pos, const glm::vec2& dims, int index);
dae::GameObject* CreatePump(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims, int direction);
dae::GameObject* CreateFire(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims);
dae::GameObject* CreateButton(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims, const std::string& texture, Command* pCommand);
dae::GameObject* CreateHighScore(dae::Scene& scene, const glm::vec2& pos, const std::string& filepath);