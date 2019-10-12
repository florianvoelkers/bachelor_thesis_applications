#pragma once

// external libraries
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

// standard library
#include <string>
#include <vector>
#include <memory>
#include <iostream>

// internal code
#include "Events/Event.hpp"

// forward declaration
class Component; // since Entity.hpp needs to be included in Component.hpp

// An entity represents one object in the application. This can be anything, e.g. the player, a lamp, a collider,
// depending on what components make up the Entity. The Entity can also have a number of entites as children.
class Entity
{
public:
	Entity(const std::string& name, unsigned int entityId, bool isActive = true);

	void AddChild(std::shared_ptr<Entity> child);
	void RemoveChild(int entityID);

	// from: https://stackoverflow.com/questions/44105058/how-does-unitys-getcomponent-work
	template<class ComponentType, typename... Args>
	void AddComponent(Args&& ... params);

	template<class ComponentType>
	ComponentType& GetComponent();

	template<class ComponentType>
	bool RemoveComponent();

	Entity* Find(const std::string& name);
	const std::vector<std::shared_ptr<Entity>>& GetChildren() const { return m_Children; }
	const std::vector<std::shared_ptr<Component>>& GetComponents() const { return m_Components; }

	void OnUpdate(float deltaTime);
	void OnEvent(Event& e);
	void Draw(const glm::mat4& view, const glm::mat4 projection);

	void SetActive(bool isActive) { m_IsActive = isActive; }
	inline const std::string GetName() const { return m_Name; }
	inline const bool GetIsActive() const { return m_IsActive; }
	inline int GetEntityID() { return m_EntityID; }

	Entity* GetParent() { return m_Parent; }
	void SetParent(Entity* parent) { m_Parent = parent; }

	bool GetParentsActive();

	static void Destroy(Entity* entity);

private:
	std::vector<std::shared_ptr<Entity>> m_Children;
	std::vector<std::shared_ptr<Component>> m_Components;
	std::string m_Name;	
	bool m_IsActive;
	int m_EntityID;
	Entity* m_Parent;
};


//***************
// Entity::AddComponent
// perfect-forwards all params to the ComponentType constructor with the matching parameter list
// DEBUG: be sure to compare the arguments of this fn to the desired constructor to avoid perfect-forwarding failure cases
// EG: deduced initializer lists, decl-only static const int members, 0|NULL instead of nullptr, overloaded fn names, and bitfields
//***************
template<class ComponentType, typename ...Args>
inline void Entity::AddComponent(Args&& ...params)
{
	m_Components.emplace_back(new ComponentType(std::forward<Args>(params)...));
}

//***************
// Entity::GetComponent
// returns the first component that matches the template type
// or that is derived from the template type
// EG: if th template type is Component, and components[0] type is BoxCollider
// then components[0] will be returned because it derives from Component
//***************
template<class ComponentType>
inline ComponentType& Entity::GetComponent()
{
	for (auto&& component : m_Components)
	{
		if (component->IsClassType(ComponentType::Type))
			return *static_cast<ComponentType*>(component.get());
	}

	return *std::unique_ptr< ComponentType >(nullptr);
}

//***************
// Entity::RemoveComponent
// returns true on successful removal
// returns false if components is empty, or no such component exists
//***************
template< class ComponentType >
bool Entity::RemoveComponent() {
	if (m_Components.empty())
		return false;

	auto& index = std::find_if(m_Components.begin(),
		m_Components.end(),
		[classType = ComponentType::Type](auto& component) {
		return component->IsClassType(classType);
	});

	bool success = index != m_Components.end();

	if (success)
		m_Components.erase(index);

	return success;
}
