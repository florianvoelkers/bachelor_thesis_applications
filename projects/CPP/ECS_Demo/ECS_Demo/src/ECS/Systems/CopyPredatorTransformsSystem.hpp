#pragma once

#include "ECS/ECS.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/PredatorComponent.hpp"

#include "Application.hpp"

class CopyPredatorTransformsSystem : public System
{
public:
	CopyPredatorTransformsSystem() : System()
	{
		AddComponentType(TransformComponent::ID);
		AddComponentType(PredatorComponent::ID);
	}

	virtual void Update(float deltaTime, BaseComponent** components) override
	{
		TransformComponent* transformComponent = (TransformComponent*)components[0];
		Application::Get().UpdatePredatorPosition(transformComponent->position);
	}
};

