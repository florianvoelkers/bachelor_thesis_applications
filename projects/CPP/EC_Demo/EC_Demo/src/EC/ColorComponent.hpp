#pragma once

// internal code
#include "Component.hpp"
#include "Application.hpp"
#include "Color.hpp"

// external libraries
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

class ColorComponent : public Component
{
	CLASS_DECLARATION(ColorComponent)

public:
	ColorComponent(Entity* entity, Color color, bool canChangeColor, bool enabled = true)
		: Component(entity, enabled), m_CanChangeColor(canChangeColor), m_Color(color)
	{
	}

	virtual void OnUpdate(float deltaTime) override
	{
		if (m_CanChangeColor)
		{
			Color oldColor = m_Color;
			float newR = oldColor.r + deltaTime;
			float newG = oldColor.g + deltaTime;
			float newB = oldColor.b + deltaTime;
			if (newR > 1.0f)
				newR = 0.0f;
			if (newG > 1.0f)
				newG = 0.0f;
			if (newB > 1.0f)
				newB = 0.0f;
			m_Color = Color(newR, newG, newB, oldColor.a);
		}		
	}

	inline Color& GetColor() { return m_Color; }

private:
	Color m_Color;
	bool m_CanChangeColor;
};



