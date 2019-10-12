#pragma once

// internal code
#include "Component.hpp"
#include "Application.hpp"
#include "EC/Transform.hpp"

// external libraries
#include <glm/glm.hpp>

class Predator : public Component
{
	CLASS_DECLARATION(AvoidPredator)

public:
	Predator(Entity* entity, bool enabled = true)
		: Component(entity, enabled)
	{
	}

	virtual void OnUpdate(float deltaTime) override
	{
		glm::vec3 position = GetEntity().GetComponent<Transform>().GetPosition();
		Application::Get().UpdatePredatorPosition(position);
	}
};

