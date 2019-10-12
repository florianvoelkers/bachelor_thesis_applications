#pragma once

#include "ECS/ECS.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/AvoidPredatorComponent.hpp"

#include <stdlib.h>

#include "Application.hpp"

class AvoidanceSystem : public System
{
public:
	AvoidanceSystem(float distanceX, float distanceY) : System(), m_DistanceX(distanceX), m_DistanceY(distanceY)
	{
		AddComponentType(TransformComponent::ID);
		AddComponentType(AvoidPredatorComponent::ID);
	}

	virtual void Update(float deltaTime, BaseComponent** components) override
	{
		TransformComponent* transformComponent = (TransformComponent*)components[0];
		AvoidPredatorComponent* avoidPredatorComponent = (AvoidPredatorComponent*)components[1];
		glm::vec3& predatorPosition = Application::Get().GetPredatorPosition();

		float actualDistanceX = std::abs(transformComponent->position.x - predatorPosition.x);
		float actualDistanceY = transformComponent->position.y - predatorPosition.y;
		if (actualDistanceX < m_DistanceX && std::abs(actualDistanceY) < m_DistanceY)
		{				
			avoidPredatorComponent->avoiding = true;
			if (actualDistanceY >= 0.0f)
			{
				transformComponent->position.y += m_DistanceY;
				avoidPredatorComponent->avoidingUp = true;					
			}
			else
			{
				transformComponent->position.y -= m_DistanceY;
				avoidPredatorComponent->avoidingUp = false;
			}
		}

		if (actualDistanceX > m_DistanceX && std::abs(actualDistanceY) < m_DistanceY * 2 && avoidPredatorComponent->avoiding)
		{
			if (avoidPredatorComponent->avoidingUp)
				transformComponent->position.y -= m_DistanceY;
			else
				transformComponent->position.y += m_DistanceY;

			avoidPredatorComponent->avoiding = false;
		}
			
	}

private:
	float m_DistanceX;
	float m_DistanceY;
};
