#pragma once

// internal code
#include "Component.hpp"
#include "Application.hpp"
#include "Transform.hpp"

// external libraries
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

class Movement : public Component
{
	CLASS_DECLARATION(Movement)

public:
	Movement(Entity* entity, float minimumMovementSpeed, float maximumMovementSpeed, bool enabled = true)
		: Component(entity, enabled)
	{
		m_MovementSpeed = glm::linearRand(minimumMovementSpeed, maximumMovementSpeed);
	}

	virtual void OnUpdate(float deltaTime) override
	{
		Transform& transform = GetEntity().GetComponent<Transform>();
		glm::vec3 oldPosition = transform.GetPosition();

		if (m_MovementSpeed > 0.0f)
		{
			if (oldPosition.x < Application::Get().rightBound)
			{
				float newX = oldPosition.x + deltaTime * m_MovementSpeed;
				transform.SetPosition(glm::vec3(newX, oldPosition.y, oldPosition.z));
			}
			else
			{
				float randomY = glm::linearRand(-40.0f, 40.0f);
				transform.SetPosition(glm::vec3(Application::Get().leftBound, randomY, oldPosition.z));
			}
		}
		else
		{
			if (oldPosition.x > Application::Get().leftBound)
			{
				float newX = oldPosition.x + deltaTime * m_MovementSpeed;
				transform.SetPosition(glm::vec3(newX, oldPosition.y, oldPosition.z));
			}
			else
			{
				float randomY = glm::linearRand(-40.0f, 40.0f);
				transform.SetPosition(glm::vec3(Application::Get().rightBound, randomY, oldPosition.z));
			}
		}
		
	}

private:
	float m_MovementSpeed;
};