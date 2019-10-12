#pragma once

#include "ECS/ECS.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/MovementComponent.hpp"
#include "Application.hpp"

#include <glm/gtc/random.hpp>

class MovementSystem : public System
{
public:
	MovementSystem() : System()
	{
		AddComponentType(TransformComponent::ID);
		AddComponentType(MovementComponent::ID);
	}

	virtual void Update(float deltaTime, BaseComponent** components) override
	{
		TransformComponent* transform = (TransformComponent*)components[0];
		MovementComponent* movement = (MovementComponent*)components[1];

		glm::vec3 oldPosition = transform->position;
		if (movement->movementSpeed > 0.0f)
		{
			if (oldPosition.x < Application::Get().rightBound)
			{
				float newX = oldPosition.x + deltaTime * movement->movementSpeed;
				transform->position = glm::vec3(newX, oldPosition.y, oldPosition.z);
			}
			else
			{
				float randomY = glm::linearRand(-40.0f, 40.0f);
				transform->position = glm::vec3(Application::Get().leftBound, randomY, oldPosition.z);
			}
		}
		else
		{
			if (oldPosition.x > Application::Get().leftBound)
			{
				float newX = oldPosition.x + deltaTime * movement->movementSpeed;
				transform->position = glm::vec3(newX, oldPosition.y, oldPosition.z);
			}
			else
			{
				float randomY = glm::linearRand(-40.0f, 40.0f);
				transform->position = glm::vec3(Application::Get().rightBound, randomY, oldPosition.z);
			}
		}

		
		
	}
};
