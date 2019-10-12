#pragma once

// internal code
#include "Component.hpp"
#include "Application.hpp"
#include "EC/Transform.hpp"

#include <stdlib.h>

// external libraries
#include <glm/glm.hpp>

class AvoidPredator : public Component
{
	CLASS_DECLARATION(AvoidPredator)

public:
	AvoidPredator(Entity* entity, float distanceX, float distanceY, bool enabled = true)
		: Component(entity, enabled), m_AvoidDistanceX(distanceX), m_AvoidDistanceY(distanceY)
	{
	}

	virtual void OnUpdate(float deltaTime) override
	{
		Transform& transform = GetEntity().GetComponent<Transform>();
		glm::vec3& predatorPosition = Application::Get().GetPredatorPosition();

		float actualDistanceX = std::abs(transform.GetPosition().x - predatorPosition.x);
		float actualDistanceY = transform.GetPosition().y - predatorPosition.y;
		glm::vec3 oldPosition = transform.GetPosition();
		if (actualDistanceX < m_AvoidDistanceX && std::abs(actualDistanceY) < m_AvoidDistanceY)
		{
			avoiding = true;
			if (actualDistanceY >= 0.0f)
			{
				transform.SetPosition(glm::vec3(oldPosition.x, oldPosition.y + m_AvoidDistanceY, oldPosition.z));
				avoidingUp = true;
			}
			else
			{
				transform.SetPosition(glm::vec3(oldPosition.x, oldPosition.y - m_AvoidDistanceY, oldPosition.z));
				avoidingUp = false;
			}
		}

		if (actualDistanceX > m_AvoidDistanceX && std::abs(actualDistanceY) < m_AvoidDistanceY * 2 && avoiding)
		{
			if (avoidingUp)
				transform.SetPosition(glm::vec3(oldPosition.x, oldPosition.y - m_AvoidDistanceY, oldPosition.z));
			else
				transform.SetPosition(glm::vec3(oldPosition.x, oldPosition.y + m_AvoidDistanceY, oldPosition.z));

			avoiding = false;
		}

	}

private:
	bool avoiding = false;
	bool avoidingUp = false;
	float m_AvoidDistanceX;
	float m_AvoidDistanceY;
};
