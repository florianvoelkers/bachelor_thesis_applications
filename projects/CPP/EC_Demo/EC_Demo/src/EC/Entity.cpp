#include "Entity.hpp"

// standard library
#include <algorithm>

// internal code
#include "Component.hpp"
#include "Transform.hpp"

Entity::Entity(const std::string& name, unsigned int entityId, bool isActive)
	: m_Name(name), m_EntityID(entityId), m_IsActive(isActive)
{
}

void Entity::AddChild(std::shared_ptr<Entity> child)
{
	m_Children.push_back(child);
	child->SetParent(this);
}

void Entity::RemoveChild(int entityID)
{
	int index = -1;
	for (int i = 0; i < m_Children.size(); i++)
	{
		if (m_EntityID == m_Children[i]->GetEntityID())
		{
			index = i;
			break;
		}
	}

	std::vector<std::shared_ptr<Entity>>::iterator iterator = m_Children.begin() + index;
	m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), *iterator));
	std::move(*iterator);
}

Entity* Entity::Find(const std::string& name)
{
	// checks if this is the GameObject we're looking for
	if (name == GetName())
		return this;

	// if not check all the children, if they return a GameObject which name is not "NULL", this is the GameObject we're looking for
	for (unsigned int i = 0; i < m_Children.size(); i++)
	{
		Entity* placeholder = m_Children[i]->Find(name);
		if (placeholder != nullptr)
			return placeholder;
	}

	// if you can't find it, return a nullptr
	return nullptr;
}

void Entity::OnUpdate(float deltaTime)
{
	if (m_IsActive)
	{
		// update itself
		for (unsigned int i = 0; i < m_Components.size(); i++)
		{
			if (m_Components[i]->GetEnabled())
				m_Components[i]->OnUpdate(deltaTime);
		}

		// update its children
		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			m_Children[i]->OnUpdate(deltaTime);
		}
	}
}

void Entity::OnEvent(Event& e)
{
	if (m_IsActive)
	{
		for (unsigned int i = 0; i < m_Components.size(); i++)
		{
			if (m_Components[i]->GetEnabled())
				m_Components[i]->OnEvent(e);
		}

		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			m_Children[i]->OnEvent(e);
		}
	}
}

void Entity::Draw(const glm::mat4& view, const glm::mat4 projection)
{
	if (m_IsActive)
	{
		for (unsigned int i = 0; i < m_Components.size(); i++)
		{
			if (m_Components[i]->GetEnabled())
				m_Components[i]->Draw(view, projection);
		}

		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			m_Children[i]->Draw(view, projection);
		}
	}
}

bool Entity::GetParentsActive()
{
	if (m_Parent != nullptr)
	{
		if (m_Parent->GetParentsActive())
			return m_IsActive;
		else
			return false;
	}
	else
		return m_IsActive;


	return false;
}

void Entity::Destroy(Entity* entity)
{
	entity->GetParent()->RemoveChild(entity->GetEntityID());
}
