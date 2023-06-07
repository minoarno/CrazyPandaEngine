#pragma once
namespace dae
{
	class GameObject;
	class Scene;
}

dae::GameObject* CreatePlayer(dae::Scene& scene);
dae::GameObject* CreatePooka(dae::Scene& scene);
dae::GameObject* CreateFygar(dae::Scene& scene);
dae::GameObject* CreateRock(dae::Scene& scene);
dae::GameObject* CreateBlock(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims);