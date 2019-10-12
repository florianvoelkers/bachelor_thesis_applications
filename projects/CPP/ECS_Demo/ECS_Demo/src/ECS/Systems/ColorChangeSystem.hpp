#pragma once

#include "ECS/ECS.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/ColorComponent.hpp"
#include "ECS/Components/ColorChangerComponent.hpp"
#include "Application.hpp"

#include <glm/gtc/random.hpp>

class ColorChangeSystem : public System
{
public:
	ColorChangeSystem() : System()
	{
		AddComponentType(ColorComponent::ID);
		AddComponentType(ColorChangerComponent::ID);
	}

	virtual void Update(float deltaTime, BaseComponent** components) override
	{
		ColorComponent* color = (ColorComponent*)components[0];

		Color oldColor = color->color;
		float newR = oldColor.r + deltaTime;
		float newG = oldColor.g + deltaTime;
		float newB = oldColor.b + deltaTime;
		if (newR > 1.0f)
			newR = 0.0f;
		if (newG > 1.0f)
			newG = 0.0f;
		if (newB > 1.0f)
			newB = 0.0f;
		color->color = Color(newR, newG, newB, oldColor.a);
	}
};
