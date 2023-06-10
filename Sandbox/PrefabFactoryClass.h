#pragma once
namespace dae
{
	class GameObject;
	class Scene;
}

dae::GameObject* CreatePlayer(dae::Scene& scene, const glm::vec2& pos);
dae::GameObject* CreatePooka(dae::Scene& scene, const glm::vec2& pos);
dae::GameObject* CreateFygar(dae::Scene& scene, const glm::vec2& pos);
dae::GameObject* CreateRock(dae::Scene& scene, const glm::vec2& pos);
dae::GameObject* CreateBlock(dae::GameObject* pLevel, const glm::vec2& pos, const glm::vec2& dims, int index);
dae::GameObject* CreatePump(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims, int direction);
dae::GameObject* CreateFire(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims);