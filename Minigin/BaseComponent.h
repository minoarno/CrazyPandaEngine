#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = default;
		BaseComponent& operator=(const BaseComponent& other) = default;
		BaseComponent(BaseComponent&& other) = default;
		BaseComponent& operator=(BaseComponent&& other) = default;
		virtual ~BaseComponent() = default;

		virtual void SetGameObject(GameObject* ownerGameObject) { m_pGameObject = ownerGameObject; }
		[[nodiscard]] GameObject* GetGameObject() const { return m_pGameObject; }
	protected:
		friend class GameObject;

		virtual void Initialize() {};
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};
		virtual void RenderImGui(){};

		GameObject* m_pGameObject{ nullptr };
	private:
		virtual void BaseInitialize();
		bool m_IsInitialized{ false };
	};
}