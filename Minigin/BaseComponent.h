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

		virtual void SetGameObject(dae::GameObject* ownerGameObject) { m_pGameObject = ownerGameObject; }
		dae::GameObject* GetGameObject() { return m_pGameObject; }
	protected:
		friend class dae::GameObject;

		virtual void Initialize() {};
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};

		dae::GameObject* m_pGameObject{ nullptr };
	private:
		virtual void BaseInitialize();
		bool m_IsInitialized{ false };
	};
}